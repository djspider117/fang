#pragma once
#include "pch.h"
#include "IFangBindable.h"
#include "VertexShader.h"

namespace Fang::Rendering::Bindables
{
	public class InputLayout : public IFangBindable
	{
	public:
		InputLayout(FangGraphics& graphics, const VertexShader* vs, const D3D11_INPUT_ELEMENT_DESC* ied, SIZE_T iedSize)
		{
			THROW_FAILED_NOHR(graphics.GetDevice()->CreateInputLayout(ied, iedSize, vs->GetShaderBytecode(), vs->GetShaderBytecodeSize(), &_inputLayout));
		}

		virtual void Bind(FangGraphics& graphics) noexcept override
		{
			graphics.GetContext()->IASetInputLayout(_inputLayout);
		}

	protected:
		CComPtr<ID3D11InputLayout> _inputLayout;
	};
}