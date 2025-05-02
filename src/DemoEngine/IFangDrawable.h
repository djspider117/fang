#pragma once
#include "pch.h"

namespace Fang::Rendering
{
	// forward decl
	class FangGraphics;

	public interface IFangDrawable
	{
		virtual void Draw(FangGraphics& graphics) = 0;
		virtual void Update(double deltaTime) = 0;
		virtual DirectX::XMMATRIX GetTransform() = 0;
	};
}