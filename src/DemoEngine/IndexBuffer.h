#pragma once
#include "BufferBindable.h"

namespace Fang::Rendering::Bindables
{
	public class IndexBuffer : public BufferBindable
	{
	public:
		IndexBuffer(FangGraphics& graphics, const USHORT* indices, UINT indicesSize)
		{
			THROW_FAILED_NOHR(CreateDefaultBuffer<USHORT>(graphics.GetDevice(), D3D11_BIND_INDEX_BUFFER, indices, indicesSize, &_buffer));
		}

		virtual void Bind(FangGraphics& graphics) noexcept override
		{
			graphics.GetContext()->IASetIndexBuffer(_buffer, DXGI_FORMAT_R16_UINT, 0);
		}

		void SetCount(UINT count) { _indicesCount = count; }
		UINT GetCount() const { return _indicesCount; }

	protected:
		UINT _indicesCount;
	};
}