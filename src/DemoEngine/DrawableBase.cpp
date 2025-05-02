#include "DrawableBase.h"
#include "pch.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffers.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "InputLayout.h"
#include "Topology.h"

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

		auto transform = DirectX::XMMatrixRotationZ(15);

		Topology* topo = new Topology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		VertexBuffer* vbuff = new VertexBuffer(gfx, vertices, std::size(vertices));
		IndexBuffer* ibuff = new IndexBuffer(gfx, indices, std::size(indices));
		ConstantBuffers* cbuff = new ConstantBuffers(gfx, &transform, 1);
		VertexShader* vs = new VertexShader(gfx, L"VertexShader.cso");
		PixelShader* ps = new PixelShader(gfx, L"PixelShader.cso");
		InputLayout* il = new InputLayout(gfx, vs, ied, std::size(ied));

		std::vector<IFangBindable*> bindables{ topo, vbuff, ibuff, cbuff, vs, ps, il };

		*ppDrawable = new DrawableBase(transform, bindables);

		return S_OK;
	}
}