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

#include "FangException.h"

// Use this macro after you defined HRESULT hr in your code
#define RETURN_FAILED(x) if(FAILED(hr = x)) return hr;

// Direct3D 11 core
#pragma comment(lib, "d3d11.lib")

// DXGI (for swap chains, etc.)
#pragma comment(lib, "dxgi.lib")

// D3DCompiler (for compiling HLSL shaders)
#pragma comment(lib, "d3dcompiler.lib")

// Optional debug layer (only works with debug device)
#pragma comment(lib, "dxguid.lib")