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
		/*_buff.Update(
			graphics,
			DirectX::XMMatrixTranspose(_parent.GetTransform()) * graphics.GetProjectionMatrix());*/
		CBuf cb;
		XMStoreFloat4x4(&cb.transform, DirectX::XMMatrixTranspose(_parent.GetTransform() * graphics.GetProjectionMatrix()));
		_buff.Update(graphics, cb);

		_buff.Bind(graphics);
	}
}
