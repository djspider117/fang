#pragma once
#include "pch.h"
#include "IFangBindable.h"
#include "BufferBindable.h"
#include "Vertex.h"

namespace Fang::Rendering::Bindables
{
	public class VertexBuffer : public BufferBindable
	{
	public:
		
		template<class T>
		VertexBuffer(FangGraphics& graphics, const T* vertices, UINT verticesSize)
		{
			THROW_FAILED_NOHR(CreateDefaultBuffer<T>(graphics.GetDevice(), D3D11_BIND_VERTEX_BUFFER, vertices, verticesSize, &_buffer));
		}

		virtual void Bind(FangGraphics& graphics) noexcept override
		{
			const UINT stride = sizeof(Vertex);
			const UINT offset = 0;

			graphics.GetContext()->IASetVertexBuffers(0, 1, &(_buffer.p), &stride, &offset);
		}
	};
}