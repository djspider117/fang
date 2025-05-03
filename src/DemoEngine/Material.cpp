#include "pch.h"
#include "Material.h"

namespace Fang::Rendering
{
	const D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "VertexColor", 0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	BasicMaterial::BasicMaterial(FangGraphics& gfx) :
		_vs(gfx, L"VertexShader.cso"),
		_ps(gfx, L"PixelShader.cso"),
		_il(gfx, &_vs, ied, std::size(ied))
	{

	}

	BasicMaterial::BasicMaterial(FangGraphics& gfx, std::wstring vsShaderPath, std::wstring psShaderPath, const D3D11_INPUT_ELEMENT_DESC* ied, UINT iedSize) :
		_vs(gfx, vsShaderPath),
		_ps(gfx, psShaderPath),
		_il(gfx, &_vs, ied, iedSize)
	{
	}

	void BasicMaterial::Bind(FangGraphics& graphics) noexcept
	{
		_vs.Bind(graphics);
		_ps.Bind(graphics);
		_il.Bind(graphics);
	}

	// =================================================

	BasicTexturedMaterial::BasicTexturedMaterial(FangGraphics& gfx, const FangTextureBGRA8& texture, std::wstring vsShaderPath, std::wstring psShaderPath, const D3D11_INPUT_ELEMENT_DESC* ied, UINT iedSize) :
		BasicMaterial(gfx, vsShaderPath, psShaderPath, ied, iedSize)
	{
		HRESULT hr;

		THROW_FAILED(LoadD3D11Texture2DFromFangTextureBGRA8(gfx, texture, &_texture, &_srv));

		D3D11_SAMPLER_DESC sd{};
		sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

		// TODO: move sampler into its own Bindable??

		THROW_FAILED(gfx.GetDevice()->CreateSamplerState(&sd, &_sampler));
	}

	void BasicTexturedMaterial::Bind(FangGraphics& graphics) noexcept
	{
		BasicMaterial::Bind(graphics);
		graphics.GetContext()->PSSetSamplers(0, 1, &(_sampler.p));
		graphics.GetContext()->PSSetShaderResources(0, 1, &(_srv.p));
	}
}