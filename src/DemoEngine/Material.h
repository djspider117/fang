#pragma once
#include "pch.h"
#include "IFangBindable.h"

#include "VertexShader.h"
#include "PixelShader.h"
#include "InputLayout.h"
#include "FangTexture2D.h"

namespace Fang::Rendering
{
	public class BasicMaterial : public IFangBindable
	{
	public:
		BasicMaterial(FangGraphics& gfx);
		BasicMaterial(FangGraphics& gfx, std::wstring vsShaderPath, std::wstring psShaderPath, const D3D11_INPUT_ELEMENT_DESC* ied, UINT iedSize);
		virtual ~BasicMaterial() = default;

		void Bind(FangGraphics& graphics) noexcept override;

	protected:
		Bindables::VertexShader _vs;
		Bindables::PixelShader _ps;
		Bindables::InputLayout _il;
	};

	public class BasicTexturedMaterial : public BasicMaterial
	{
	public:
		BasicTexturedMaterial(FangGraphics& gfx, const FangTextureBGRA8& texture, std::wstring vsShaderPath, std::wstring psShaderPath, const D3D11_INPUT_ELEMENT_DESC* ied, UINT iedSize);
		virtual ~BasicTexturedMaterial() = default;

		void Bind(FangGraphics& graphics) noexcept override;

	protected:
		CComPtr<ID3D11Texture2D> _texture; // we might remove this if we don't need it
		CComPtr<ID3D11ShaderResourceView> _srv;
		CComPtr<ID3D11SamplerState> _sampler;
	};
}