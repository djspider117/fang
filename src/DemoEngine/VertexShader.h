#pragma once
#include "pch.h"
#include "IFangBindable.h"

namespace Fang::Rendering::Bindables
{
	public class VertexShader : public IFangBindable
	{
	public:
		VertexShader(FangGraphics& graphics, std::wstring shaderPath)
		{
			HRESULT hr;
			THROW_FAILED(D3DReadFileToBlob(graphics.GetShaderPath(shaderPath).c_str(), &_vsBlob));
			THROW_FAILED(graphics.GetDevice()->CreateVertexShader(_vsBlob->GetBufferPointer(), _vsBlob->GetBufferSize(), nullptr, &_vertexShader));
			_ownsShaderBlob = true;
		}

		VertexShader(FangGraphics& graphics, ID3DBlob* pBlob)
		{
			_externalShaderBytecode = pBlob->GetBufferPointer();
			_externalBytecodeSize = pBlob->GetBufferSize();

			THROW_FAILED_NOHR(graphics.GetDevice()->CreateVertexShader(_externalShaderBytecode, _externalBytecodeSize, nullptr, &_vertexShader));
		}

		VertexShader(FangGraphics& graphics, const void* shaderBytecode, SIZE_T shaderBytecodeSize)
		{
			_externalShaderBytecode = shaderBytecode;
			_externalBytecodeSize = shaderBytecodeSize;

			THROW_FAILED_NOHR(graphics.GetDevice()->CreateVertexShader(shaderBytecode, shaderBytecodeSize, nullptr, &_vertexShader));
		}

		virtual void Bind(FangGraphics& graphics) noexcept override
		{
			graphics.GetContext()->VSSetShader(_vertexShader, nullptr, 0);
		}

		const void* GetShaderBytecode() const noexcept
		{
			if (_ownsShaderBlob)
				return _vsBlob->GetBufferPointer();

			return _externalShaderBytecode;
		}

		SIZE_T GetShaderBytecodeSize() const noexcept
		{
			if (_ownsShaderBlob)
				return _vsBlob->GetBufferSize();

			return _externalBytecodeSize;
		}

	protected:
		CComPtr<ID3D11VertexShader> _vertexShader;
		CComPtr<ID3DBlob> _vsBlob;

		// do not destroy, externally owned
		const void* _externalShaderBytecode;
		SIZE_T _externalBytecodeSize;

		bool _ownsShaderBlob;
	};
}