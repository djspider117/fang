#pragma once
#include "pch.h"
#include "IFangBindable.h"
#include "FangGraphics.h"
#include "IFangDrawable.h"
#include "ConstantBuffers.h"

namespace Fang::Rendering::Bindables
{
	public class TransformConstantBuffer : public IFangBindable
	{
	public:
		TransformConstantBuffer(FangGraphics&, const IFangDrawable& parent);
		void Bind(FangGraphics& graphics) noexcept override;

	private:
		VertexConstantBuffer<DirectX::XMMATRIX> _buff;
		const IFangDrawable& _parent;
	};
}