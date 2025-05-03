#include "pch.h"
#include "FangEngine.h"
#include "FangDev.h"
#include <msclr/marshal_cppstd.h>
#include "DemoCube.h"
#include "GraphicsScene.h"
#include "Material.h"
#include "TextureLoader.h"

namespace Fang
{
	const D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "VertexColor", 0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	FangEngine::FangEngine(IntPtr^ swapChainPanelNativePtr, String^ shaderCacheLocation) :
		_swapChainPanelNativePtr(reinterpret_cast<ISwapChainPanelNative*>(swapChainPanelNativePtr->ToPointer())),
		_shaderCacheLocation(shaderCacheLocation) {
	}

	FangEngine::~FangEngine()
	{
		_initialized = false;
		delete _graphicsSubsystem;
	}

	void FangEngine::Initialize(UINT width, UINT height)
	{
		msclr::interop::marshal_context context;
		_graphicsSubsystem = new FangGraphics(_swapChainPanelNativePtr, context.marshal_as<std::wstring>(_shaderCacheLocation));

		ThrowIfFailed(_graphicsSubsystem->CreateDeviceResources());
		ThrowIfFailed(_graphicsSubsystem->CreateSizeDependentResources(width, height));

		try
		{
			auto aspectRatio = width / (float)height;
			auto* rv = new GraphicsScene();

			auto* camera = new Camera(aspectRatio, XM_PIDIV4, 0.004f, 1000.0f);
			rv->SetCurrentCamera(camera);
			_camInterop = gcnew CameraInterop(camera);

			auto mat1 = new BasicMaterial(*_graphicsSubsystem, L"VertexShader.cso", L"PixelShader.cso", ied, std::size(ied));
			auto mat2 = new BasicMaterial(*_graphicsSubsystem, L"VertexShader.cso", L"WonkyShader.cso", ied, std::size(ied));
		
			TextureLoader ld;
			auto texData = ld.LoadTexture(L"C:\\Work\\fang\\src\\Textures\\demoTex.jpg");

			auto mat3 = new BasicTexturedMaterial(*_graphicsSubsystem, *texData, L"TexVS.cso", L"TexPS.cso", VertexUV::InputLayoutElements, 2);
			delete texData;

			rv->StoreMaterial(L"mat1", mat1);
			rv->StoreMaterial(L"mat2", mat2);

			for (size_t i = 0; i < 10; i++)
			{
				auto even = i % 2 == 0;
				auto mat = even ? mat1 : mat2;
				auto cube = new Rendering::Drawables::DemoCube(*_graphicsSubsystem, mat);
				cube->OffsetX = (i / 10.0f) * 10 + -5;
				cube->UseSin = i % 2 == 0;
				rv->AddDrawable(cube);
			}

			auto texCube = new Rendering::Drawables::DemoCube(*_graphicsSubsystem, mat3, true);
			rv->AddDrawable(texCube);

			_graphicsSubsystem->SetScene(rv);
		}
		catch (const Core::HResultException& ex)
		{
			ThrowIfFailed(ex.GetHR());
		}

		_initialized = true;
	}

	void FangEngine::HandleSizeChanged(UINT width, UINT height)
	{
		// memory leaks here
		_initialized = false;

		ThrowIfFailed(_graphicsSubsystem->Stop());
		delete _graphicsSubsystem;
		_graphicsSubsystem = nullptr;

		Initialize(width, height);
	}

	void FangEngine::Tick(double deltaTime)
	{
		if (!_initialized)
			return;

		_graphicsSubsystem->Render(deltaTime);
	}
}