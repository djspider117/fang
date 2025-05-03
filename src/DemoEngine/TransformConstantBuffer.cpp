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
		_buff.Update(graphics, DirectX::XMMatrixTranspose(_parent.GetTransform() * graphics.GetProjectionMatrix()));
		_buff.Bind(graphics);
	}

	SharedTransformConstantBuffer::SharedTransformConstantBuffer(FangGraphics&, const IFangDrawable& parent) :
		_parent(parent)
	{
	}

	void SharedTransformConstantBuffer::Bind(FangGraphics& graphics) noexcept
	{
		if (_buff == nullptr)
		{
			_buff = std::make_unique<VertexConstantBuffer<DirectX::XMMATRIX>>(graphics);
		}
		else
		{
			_buff->Update(graphics, DirectX::XMMatrixTranspose(_parent.GetTransform() * graphics.GetProjectionMatrix()));
			_buff->Bind(graphics);
		}
	}

	std::unique_ptr<VertexConstantBuffer<DirectX::XMMATRIX>> SharedTransformConstantBuffer::_buff;
}
