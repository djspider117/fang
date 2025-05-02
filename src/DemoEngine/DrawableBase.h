#pragma once
#include "IFangDrawable.h"
#include <vector>
#include "IFangBindable.h"

namespace Fang::Rendering::Drawables
{
	public class DrawableBase : public IFangDrawable
	{
	public:
		DrawableBase(XMMATRIX transform, std::vector<IFangBindable*> bindables)
			: _bindables(bindables), _transform(transform)
		{
		}

		virtual void Update(double deltaTime) override
		{
			//do nothing, yet
		}

		virtual void Draw(FangGraphics& graphics) override
		{
			for (auto bindable : _bindables)
			{
				bindable->Bind(graphics);
			}
		}

		virtual DirectX::XMMATRIX GetTransform() override
		{
			// const ref?
			return _transform;
		}

	protected:
		std::vector<IFangBindable*> _bindables; //currently unsafe + no destructor, see smart pointers
		XMMATRIX _transform;
	};

	static HRESULT CreateDemoDrawable(DrawableBase** ppDrawable);
}