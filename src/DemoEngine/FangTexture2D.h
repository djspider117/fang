#pragma once
#include "pch.h"
#include <vector>
#include "FangGraphics.h"

namespace Fang::Rendering
{
	struct ColorBGRA8
	{
		byte B, G, R, A;
	};

	public struct FangTextureBGRA8
	{
		std::vector<ColorBGRA8> Data;
		UINT Width;
		UINT Height;
		UINT Stride;
	};

	HRESULT LoadD3D11Texture2DFromFangTextureBGRA8(const FangGraphics& gfx, const FangTextureBGRA8& textureData, ID3D11Texture2D** ppTexture, ID3D11ShaderResourceView** ppShaderResView);
}