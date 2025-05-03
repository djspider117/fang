#include "pch.h"
#include "TransformConstantBuffer.h"

namespace Fang::Rendering::Bindables
{
	TransformConstantBuffer::TransformConstantBuffer(FangGraphics& gfx, const IFangDrawable& parent) :
		_parent(parent), _buff(gfx)
	{

	}

	void TransformConstantBuffer::Bind(FangGraphics& graphics) noexcept
	{
		_buff.Update(
			graphics,
			DirectX::XMMatrixTranspose(_parent.GetTransform()) * graphics.GetProjectionMatrix());

		_buff.Bind(graphics);
	}
}
