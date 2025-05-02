#pragma once
#include "pch.h"
#include "IFangBindable.h"
#include "BufferBindable.h"

namespace Fang::Rendering::Bindables
{

	public class VertexBuffer : public BufferBindable
	{
	public:
		VertexBuffer(FangGraphics& graphics)
		{
			THROW_FAILED_NOHR(CreateDefaultBuffer<Vertex>(D3D11_BIND_VERTEX_BUFFER, nullptr, 0, &_buffer));
		}

		VertexBuffer(FangGraphics& graphics, const Vertex* vertices, UINT verticesSize)
		{
			THROW_FAILED_NOHR(CreateDefaultBuffer<Vertex>(D3D11_BIND_VERTEX_BUFFER, vertices, verticesSize, &_buffer));
		}

		virtual void Bind(FangGraphics& graphics) noexcept override
		{
			const UINT stride = sizeof(Vertex);
			const UINT offset = 0;

			graphics.GetContext()->IASetVertexBuffers(0, 1, &(_buffer.p), &stride, &offset);
		}
	};
}