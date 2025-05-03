#pragma once
#include "pch.h"
#include "IFangBindable.h"
#include "FangGraphics.h"
#include "IFangDrawable.h"
#include "ConstantBuffers.h"

namespace Fang::Rendering::Bindables
{
	struct alignas(16) CBuf
	{
		DirectX::XMFLOAT4X4 transform;
	};


	public class TransformConstantBuffer : public IFangBindable
	{
	public:
		TransformConstantBuffer(FangGraphics&, const IFangDrawable& parent);
		void Bind(FangGraphics& graphics) noexcept override;

	private:
		VertexConstantBuffer<CBuf> _buff;
		const IFangDrawable& _parent;
	};
}