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

#include "IndexedMesh.h"
#include "Material.h"

namespace Fang::Rendering::Drawables
{
	const ColoredVertex vertices[] =
	{
		// Front face
		{ -0.5f,  0.5f, 0, 255, 0, 0 }, // 0: top-left front
		{ 0.5f,  0.5f, 0, 255, 255, 0 }, // 1: top-right front
		{ 0.5f, -0.5f, 0, 255, 0, 255 }, // 2: bottom-right front
		{ -0.5f, -0.5f, 0, 0 , 255, 255 }, // 3: bottom-left front

		// Back face
		{ -0.5f,  0.5f,  1, 0, 0, 255 }, // 4: top-left back
		{ 0.5f,  0.5f,  1, 255, 0, 255 }, // 5: top-right back
		{ 0.5f, -0.5f,  1, 0, 255, 0 }, // 6: bottom-right back
		{ -0.5f, -0.5f,  1, 255, 0, 0 }, // 7: bottom-left back
	};

	const VertexUV uv_vertices[] =
	{
		// Front face (z = 0.5)
		{ -0.5f,  0.5f,  0.5f, 0.0f, 0.0f }, // top-left
		{  0.5f,  0.5f,  0.5f, 1.0f, 0.0f }, // top-right
		{  0.5f, -0.5f,  0.5f, 1.0f, 1.0f }, // bottom-right
		{ -0.5f, -0.5f,  0.5f, 0.0f, 1.0f }, // bottom-left

		// Back face (z = -0.5)
		{  0.5f,  0.5f, -0.5f, 0.0f, 0.0f }, // top-left
		{ -0.5f,  0.5f, -0.5f, 1.0f, 0.0f }, // top-right
		{ -0.5f, -0.5f, -0.5f, 1.0f, 1.0f }, // bottom-right
		{  0.5f, -0.5f, -0.5f, 0.0f, 1.0f }, // bottom-left

		// Left face (x = -0.5)
		{ -0.5f,  0.5f, -0.5f, 0.0f, 0.0f }, // top-left
		{ -0.5f,  0.5f,  0.5f, 1.0f, 0.0f }, // top-right
		{ -0.5f, -0.5f,  0.5f, 1.0f, 1.0f }, // bottom-right
		{ -0.5f, -0.5f, -0.5f, 0.0f, 1.0f }, // bottom-left

		// Right face (x = 0.5)
		{  0.5f,  0.5f,  0.5f, 0.0f, 0.0f }, // top-left
		{  0.5f,  0.5f, -0.5f, 1.0f, 0.0f }, // top-right
		{  0.5f, -0.5f, -0.5f, 1.0f, 1.0f }, // bottom-right
		{  0.5f, -0.5f,  0.5f, 0.0f, 1.0f }, // bottom-left

		// Top face (y = 0.5)
		{ -0.5f,  0.5f, -0.5f, 0.0f, 0.0f }, // top-left
		{  0.5f,  0.5f, -0.5f, 1.0f, 0.0f }, // top-right
		{  0.5f,  0.5f,  0.5f, 1.0f, 1.0f }, // bottom-right
		{ -0.5f,  0.5f,  0.5f, 0.0f, 1.0f }, // bottom-left

		// Bottom face (y = -0.5)
		{ -0.5f, -0.5f,  0.5f, 0.0f, 0.0f }, // top-left
		{  0.5f, -0.5f,  0.5f, 1.0f, 0.0f }, // top-right
		{  0.5f, -0.5f, -0.5f, 1.0f, 1.0f }, // bottom-right
		{ -0.5f, -0.5f, -0.5f, 0.0f, 1.0f }, // bottom-left
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

	const uint16_t uv_indices[] =
	{
		// Front face
		0, 1, 2,  0, 2, 3,

		// Back face
		4, 5, 6,  4, 6, 7,

		// Left face
		8, 9,10,  8,10,11,

		// Right face
	   12,13,14, 12,14,15,

	   // Top face
	  16,17,18, 16,18,19,

	  // Bottom face
	 20,21,22, 20,22,23
	};



	const D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "VertexColor", 0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};


	DemoCube::DemoCube(FangGraphics& gfx) : DemoCube(gfx, L"PixelShader.cso")
	{

	}

	DemoCube::DemoCube(FangGraphics& gfx, BasicMaterial* mat, bool useUVVertex)
	{
		IndexedMesh* mesh = nullptr;

		if (useUVVertex)
		{
			mesh = new IndexedMesh(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST, uv_vertices, sizeof(uv_vertices), uv_indices, sizeof(uv_indices), std::size(uv_indices));
			_textured = true;
		}
		else
			mesh = new IndexedMesh(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST, vertices, sizeof(vertices), indices, sizeof(indices), std::size(indices));
		auto* tcb = new SharedTransformConstantBuffer(gfx, *this);

		AddBindable(mesh);
		SetIndexBuffer(mesh->GetIndexBufferPointer());

		AddBindable(mat);

		AddBindable(tcb);
	}

	DemoCube::DemoCube(FangGraphics& gfx, std::wstring psShaderPath) :
		DemoCube(gfx, new BasicMaterial(gfx, L"VertexShader.cso", psShaderPath, ied, std::size(ied)))
	{
	}

	void DemoCube::Update(double deltaTime)
	{
		_curTime += deltaTime;
		_rotX += 1 * deltaTime;
	}
	DirectX::XMMATRIX DemoCube::GetTransform() const
	{
		if (_textured)
			return DirectX::XMMatrixScaling(25, 25, 25) * DirectX::XMMatrixRotationZ(_rotX / 6) * DirectX::XMMatrixRotationY(_rotX /6 );

		if (UseSin)
			return DirectX::XMMatrixRotationZ(_rotX) * DirectX::XMMatrixRotationY(_rotX) * DirectX::XMMatrixTranslation(OffsetX, 2.0f, (sin(_rotX) + 1) * 5 + 3);

		return DirectX::XMMatrixRotationZ(-_rotX) * DirectX::XMMatrixRotationX(-_rotX) * DirectX::XMMatrixTranslation(OffsetX, -2.0f, (cos(_rotX) + 1) * 5 + 3);
	}
}