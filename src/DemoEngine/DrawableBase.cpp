#include "DrawableBase.h"
#include "pch.h"

#include "VertexBuffer.h"
#include "ConstantBuffers.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "InputLayout.h"
#include "Topology.h"
#include "Vertex.h"
#include "IndexBuffer.h"

using namespace Fang::Rendering::Bindables;

namespace Fang::Rendering::Drawables
{
	HRESULT CreateDemoDrawable(FangGraphics& gfx, IFangDrawable** ppDrawable)
	{
		const Vertex vertices[] =
		{
			// Front face
			{ -0.5f,  0.5f, 0, 255, 0, 0 }, // 0: top-left front
			{  0.5f,  0.5f, 0, 255, 0, 0 }, // 1: top-right front
			{  0.5f, -0.5f, 0, 255, 0, 0 }, // 2: bottom-right front
			{ -0.5f, -0.5f, 0, 255, 0, 0 }, // 3: bottom-left front

			// Back face
			{ -0.5f,  0.5f,  0.5f, 0, 0, 255}, // 4: top-left back
			{  0.5f,  0.5f,  0.5f, 0, 0, 255}, // 5: top-right back
			{  0.5f, -0.5f,  0.5f, 0, 0, 255}, // 6: bottom-right back
			{ -0.5f, -0.5f,  0.5f, 0, 0, 255}, // 7: bottom-left back
		};

		const USHORT indices[] =
		{
			// Front face
			0, 1, 2,
			0, 2, 3,

			// Back face
			5, 4, 7,
			5, 7, 6,

			// Left face
			4, 0, 3,
			4, 3, 7,

			// Right face
			1, 5, 6,
			1, 6, 2,

			// Top face
			4, 5, 1,
			4, 1, 0,

			// Bottom face
			3, 2, 6,
			3, 6, 7
		};

		const D3D11_INPUT_ELEMENT_DESC ied[] =
		{
			{ "Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{ "VertexColor", 0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};

		DemoBuffer transform = { DirectX::XMMatrixRotationZ(15) };

		Topology* topo = new Topology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		VertexBuffer* vbuff = new VertexBuffer(gfx, vertices, sizeof(vertices));
		IndexBuffer* ibuff = new IndexBuffer(gfx, indices, sizeof(indices));
		ConstantBufferBase<DemoBuffer>* cbuff = new VertexConstantBuffer<DemoBuffer>(gfx, transform);
		VertexShader* vs = new VertexShader(gfx, L"VertexShader.cso");
		PixelShader* ps = new PixelShader(gfx, L"PixelShader.cso");
		InputLayout* il = new InputLayout(gfx, vs, ied, std::size(ied));

		auto rv = new DrawableBase(transform.transform);
		rv->AddBindable(topo);
		rv->AddBindable(vbuff);
		rv->AddBindable(cbuff);
		rv->AddBindable(vs);
		rv->AddBindable(ps);
		rv->AddBindable(il);
		rv->SetIndexBuffer(ibuff);

		*ppDrawable = rv;

		return S_OK;
	}

	inline void DrawableBase::AddBindable(IFangBindable* bindable) noexcept
	{
		_bindables.push_back(bindable);
	}

	inline void DrawableBase::SetIndexBuffer(IndexBuffer* ibuff) noexcept
	{
		_indexBuffer = ibuff;
		_bindables.push_back((IFangBindable*)_indexBuffer);
	}

	inline void DrawableBase::Update(double deltaTime)
	{
		//do nothing, yet
	}

	inline void DrawableBase::Draw(FangGraphics& graphics)
	{
		for (auto& bindable : _bindables)
		{
			bindable->Bind(graphics);
		}
		graphics.GetContext()->DrawIndexed(_indexBuffer->GetCount(), 0, 0);
	}
}