#pragma once

#include "pch.h"
#include "DrawableBase.h"
#include "FangGraphics.h"

namespace Fang::Rendering::Drawables
{
	public class DemoCube : public DrawableBase
	{
	public:
		DemoCube(FangGraphics& gfx);

		virtual void Update(double deltaTime) override;
		virtual DirectX::XMMATRIX GetTransform() const override;

	private:
		float _rotX;
	};
}

