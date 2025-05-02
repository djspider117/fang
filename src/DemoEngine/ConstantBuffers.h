#pragma once
#include "pch.h"
#include "BufferBindable.h"

namespace Fang::Rendering::Bindables
{
	template<typename T>
	public class ConstantBufferBase : public BufferBindable
	{
	public:
		ConstantBufferBase(FangGraphics& graphics, const T& consts)
		{
			HRESULT hr;
			D3D11_BUFFER_DESC bufferDesc{};
			bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			bufferDesc.StructureByteStride = 0;
			bufferDesc.ByteWidth = sizeof(consts);
			bufferDesc.CPUAccessFlags = 0;

			//bufferDesc.Usage = D3D11_USAGE_DEFAULT;
			bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
			bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

			D3D11_SUBRESOURCE_DATA subresData{};
			subresData.pSysMem = &consts;

			THROW_FAILED(graphics.GetDevice()->CreateBuffer(&bufferDesc, &subresData, &_buffer));
		}
		ConstantBufferBase(FangGraphics& graphics)
		{
			HRESULT hr;
			D3D11_BUFFER_DESC bufferDesc{};
			bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			bufferDesc.StructureByteStride = 0;
			bufferDesc.ByteWidth = sizeof(T);
			bufferDesc.CPUAccessFlags = 0;

			//bufferDesc.Usage = D3D11_USAGE_DEFAULT;
			bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
			bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

			THROW_FAILED(graphics.GetDevice()->CreateBuffer(&bufferDesc, nullptr, &_buffer));
		}

		void Update(FangGraphics& gfx, const T& consts)
		{
			auto ctx = gfx.GetContext();
			D3D11_MAPPED_SUBRESOURCE msr;
			ctx->Map(_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
			memcpy(msr.pData, &consts, sizeof(consts));
			ctx->Unmap(_buffer, 0);
		}
	};

	template<typename T>
	public class VertexConstantBuffer : public ConstantBufferBase<T>
	{
		using ConstantBufferBase<T>::_buffer;

	public:
		using ConstantBufferBase<T>::ConstantBufferBase;

		void Bind(FangGraphics& gfx) noexcept override
		{
			gfx.GetContext()->VSSetConstantBuffers(0, 1, &(_buffer.p));
		}
	};

	template<typename T>
	public class PixelConstantBuffer : public ConstantBufferBase<T>
	{
		using ConstantBufferBase<T>::_buffer;
	public:
		using ConstantBufferBase<T>::ConstantBufferBase;

		void Bind(FangGraphics& gfx) noexcept override
		{
			gfx.GetContext()->PSSetConstantBuffers(0, 1, &(_buffer.p));
		}
	};
}