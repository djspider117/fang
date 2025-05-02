#pragma once
#include "pch.h"
#include "IFangBindable.h"

namespace Fang::Rendering::Bindables
{
	public class PixelShader : public IFangBindable
	{
	public:
		PixelShader(FangGraphics& graphics, std::wstring shaderPath)
		{
			HRESULT hr;
			CComPtr<ID3DBlob> psBlob;
			THROW_FAILED(D3DReadFileToBlob(graphics.GetShaderPath(shaderPath).c_str(), &psBlob));
			THROW_FAILED(graphics.GetDevice()->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(), nullptr, &_pixelShader));
		}

		PixelShader(FangGraphics& graphics, ID3DBlob* pBlob)
		{
			THROW_FAILED_NOHR(graphics.GetDevice()->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &_pixelShader));
		}

		PixelShader(FangGraphics& graphics, const void* shaderBytecode, SIZE_T shaderBytecodeSize)
		{
			THROW_FAILED_NOHR(graphics.GetDevice()->CreatePixelShader(shaderBytecode, shaderBytecodeSize, nullptr, &_pixelShader));
		}

		virtual void Bind(FangGraphics& graphics) noexcept override
		{
			graphics.GetContext()->PSSetShader(_pixelShader, nullptr, 0);
		}

	protected:
		CComPtr<ID3D11PixelShader> _pixelShader;
	};
}