#pragma once

#include "pch.h"
#include "DrawableBase.h"
#include "FangGraphics.h"

namespace Fang::Rendering
{
	class BasicMaterial;
}

namespace Fang::Rendering::Drawables
{
	public class DemoCube : public DrawableBase
	{
	public:
		DemoCube(FangGraphics& gfx);
		DemoCube(FangGraphics& gfx, BasicMaterial* mat, bool useUVVertex = false);
		DemoCube(FangGraphics& gfx, std::wstring psShaderPath);

		virtual void Update(double deltaTime) override;
		virtual DirectX::XMMATRIX GetTransform() const override;

		bool UseSin = true;
		float OffsetX = 0;
	private:
		float _rotX;
		float _curTime;
		bool _textured;
	};
}

