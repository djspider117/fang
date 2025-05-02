#pragma once
#include "pch.h"
#include "FangGraphics.h"

namespace Fang::Rendering
{
	public interface IFangDrawable
	{
		virtual void Draw(FangGraphics& graphics) = 0;
		virtual void Update(double deltaTime) = 0;
		virtual DirectX::XMMATRIX GetTransform() = 0;
	};
}