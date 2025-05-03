#pragma once
#include "pch.h"
#include "FangTexture2D.h"
#include <wincodec.h>

namespace Fang::Rendering
{
	public class TextureLoader
	{
	public:
		TextureLoader();

		FangTextureBGRA8* LoadTexture(std::wstring filePath);

	private:
		CComPtr<IWICImagingFactory> _wicFactory;
	};
}