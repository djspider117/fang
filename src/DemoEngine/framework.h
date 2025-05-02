#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>
#include <atlbase.h>
#include <windows.ui.xaml.media.dxinterop.h>

#include <d3d11.h>
#include <dxgi1_2.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#include "FangExceptionNative.h"

// Use this macro after you defined HRESULT hr in your code
#define RETURN_FAILED(x) if(FAILED(hr = x)) return hr;
#define THROW_FAILED(x) if(FAILED(hr = x)) throw Fang::Core::HResultException(hr);
#define THROW_FAILED_NOHR(x) HRESULT hr = S_OK; if(FAILED(hr = x)) throw Fang::Core::HResultException(hr);

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")