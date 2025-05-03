#include "pch.h"
#include "TextureLoader.h"


namespace Fang::Rendering
{
	TextureLoader::TextureLoader()
	{
		THROW_FAILED_NOHR(CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&_wicFactory)));
	}

	FangTextureBGRA8* TextureLoader::LoadTexture(std::wstring filePath)
	{
		HRESULT hr;

		FangTextureBGRA8* rv = new FangTextureBGRA8();

		COM_INIT(IWICBitmapDecoder, decoder, _wicFactory->CreateDecoderFromFilename(filePath.c_str(), nullptr, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &decoder));
		COM_INIT(IWICBitmapFrameDecode, frame, decoder->GetFrame(0, &frame));
		COM_INIT(IWICFormatConverter, converter, _wicFactory->CreateFormatConverter(&converter));

		THROW_FAILED(converter->Initialize(frame, GUID_WICPixelFormat32bppBGRA, WICBitmapDitherTypeNone, nullptr, 0.0, WICBitmapPaletteTypeCustom));
		THROW_FAILED(converter->GetSize(&(rv->Width), &(rv->Height)));

		rv->Stride = rv->Width * sizeof(ColorBGRA8);
		rv->Data.resize(size_t(rv->Stride * rv->Height));

		THROW_FAILED(converter->CopyPixels(nullptr, rv->Stride, (UINT)rv->Data.size(), reinterpret_cast<BYTE*>(rv->Data.data())));

		return rv;
	}
}
