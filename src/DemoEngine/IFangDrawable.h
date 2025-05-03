#pragma once
#include "pch.h"
#include <memory>
#include "FangGraphics.h"

namespace Fang::Rendering::Bindables
{
	class IndexBuffer;
}

namespace Fang::Rendering
{
	public interface IFangDrawable
	{
		virtual void Draw(FangGraphics& graphics) = 0;
		virtual void AddBindable(struct IFangBindable* bindable) noexcept = 0;
		virtual void SetIndexBuffer(const Fang::Rendering::Bindables::IndexBuffer* ibuff) noexcept = 0;
		virtual void Update(double deltaTime) = 0;
		virtual DirectX::XMMATRIX GetTransform() const = 0;
	};
}