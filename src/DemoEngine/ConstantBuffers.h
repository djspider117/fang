#pragma once
#include "pch.h"
#include "BufferBindable.h"

namespace Fang::Rendering::Bindables
{
	public class ConstantBuffers : public BufferBindable
	{
	public:
		ConstantBuffers(FangGraphics& graphics, const void* initData, SIZE_T initDataSize)
		{
			// TODO: replace ConstantBuffer with idk?

			HRESULT hr;
			D3D11_BUFFER_DESC bufferDesc{};
			bufferDesc.Usage = D3D11_USAGE_DEFAULT;
			bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			bufferDesc.StructureByteStride = sizeof(ConstantBuffer);
			bufferDesc.ByteWidth = initDataSize;
			bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

			D3D11_SUBRESOURCE_DATA subresData{};
			subresData.pSysMem = initData;

			THROW_FAILED(graphics.GetDevice()->CreateBuffer(&bufferDesc, &subresData, &_buffer));
		}

		virtual void Bind(FangGraphics& gfx) noexcept
		{
			gfx.GetContext()->VSSetConstantBuffers(0, 1, &(_buffer.p));
		}
	};
}