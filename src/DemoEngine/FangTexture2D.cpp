#include "pch.h"
#include "FangTexture2D.h"
#include "FangGraphics.h"

namespace Fang::Rendering
{
    HRESULT LoadD3D11Texture2DFromFangTextureBGRA8(const FangGraphics& gfx, const FangTextureBGRA8& textureData, ID3D11Texture2D** ppTexture, ID3D11ShaderResourceView** ppShaderResView)
    {
        HRESULT hr = S_OK;

        auto* device = gfx.GetDevice();

        D3D11_TEXTURE2D_DESC td{};
        td.Width = textureData.Width;
        td.Height = textureData.Height;
        td.MipLevels = 1;
        td.ArraySize = 1;
        td.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
        td.SampleDesc.Count = 1; //no AA
        td.SampleDesc.Quality = 0;
        td.Usage = D3D11_USAGE_DEFAULT;
        td.BindFlags = D3D11_BIND_SHADER_RESOURCE;
        td.CPUAccessFlags = 0;
        td.MiscFlags = 0;

        D3D11_SUBRESOURCE_DATA sd{};
        sd.pSysMem = textureData.Data.data();
        sd.SysMemPitch = textureData.Stride;

        RETURN_FAILED(device->CreateTexture2D(&td, &sd, ppTexture));

        D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc{};
        srvDesc.Format = td.Format;
        srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        srvDesc.Texture2D.MostDetailedMip = 0;
        srvDesc.Texture2D.MipLevels = 1;

        RETURN_FAILED(device->CreateShaderResourceView(*ppTexture, &srvDesc, ppShaderResView));

        return hr;
    }
}
