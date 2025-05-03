#include "pch.h"
#include "DemoCube.h"

#include "VertexBuffer.h"
#include "ConstantBuffers.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "InputLayout.h"
#include "Topology.h"
#include "Vertex.h"
#include "IndexBuffer.h"
#include "TransformConstantBuffer.h"

namespace Fang::Rendering::Drawables
{

	DemoCube::DemoCube(FangGraphics& gfx) : DrawableBase()
	{
		const Vertex vertices[] =
		{
			// Front face
			{ -0.5f,  0.5f, 0, 255, 0, 0 }, // 0: top-left front
			{ 0.5f,  0.5f, 0, 255, 0, 0 }, // 1: top-right front
			{ 0.5f, -0.5f, 0, 255, 0, 0 }, // 2: bottom-right front
			{ -0.5f, -0.5f, 0, 255, 0, 0 }, // 3: bottom-left front

			// Back face
			{ -0.5f,  0.5f,  0.5f, 0, 0, 255 }, // 4: top-left back
			{ 0.5f,  0.5f,  0.5f, 0, 0, 255 }, // 5: top-right back
			{ 0.5f, -0.5f,  0.5f, 0, 0, 255 }, // 6: bottom-right back
			{ -0.5f, -0.5f,  0.5f, 0, 0, 255 }, // 7: bottom-left back
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
			{ "Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "VertexColor", 0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};

		DemoBuffer transform = { DirectX::XMMatrixRotationZ(15) };

		Topology* topo = new Topology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		VertexBuffer* vbuff = new VertexBuffer(gfx, vertices, sizeof(vertices));
		IndexBuffer* ibuff = new IndexBuffer(gfx, indices, sizeof(indices));
		ibuff->SetCount(36);

		VertexShader* vs = new VertexShader(gfx, L"VertexShader.cso");
		PixelShader* ps = new PixelShader(gfx, L"PixelShader.cso");
		InputLayout* il = new InputLayout(gfx, vs, ied, std::size(ied));

		TransformConstantBuffer* tcb = new TransformConstantBuffer(gfx, *this);

		AddBindable(topo);
		AddBindable(vbuff);
		AddBindable(vs);
		AddBindable(ps);
		AddBindable(il);
		AddBindable(tcb);
		SetIndexBuffer(ibuff);
	}

	void DemoCube::Update(double deltaTime)
	{
		_rotX += sin(4 * deltaTime) * 40;
	}
	DirectX::XMMATRIX DemoCube::GetTransform() const
	{
		return DirectX::XMMatrixRotationZ(_rotX) * DirectX::XMMatrixRotationX(_rotX);
	}
}