#pragma once
#include "pch.h"
#include <memory>

namespace Fang::Rendering::Bindables
{
	class IndexBuffer;
}

namespace Fang::Rendering
{
	// forward decl
	class FangGraphics;

	public interface IFangDrawable
	{
		virtual void Draw(FangGraphics& graphics) = 0;
		virtual void AddBindable(struct IFangBindable* bindable) noexcept = 0;
		virtual void SetIndexBuffer(Fang::Rendering::Bindables::IndexBuffer* ibuff) noexcept = 0;
		virtual void Update(double deltaTime) = 0;
		virtual DirectX::XMMATRIX GetTransform() = 0;
	};
}