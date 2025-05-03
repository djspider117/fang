#include "pch.h"
#include "DrawableBase.h"

using namespace Fang::Rendering::Bindables;

namespace Fang::Rendering::Drawables
{
	void DrawableBase::AddBindable(IFangBindable* bindable) noexcept
	{
		_bindables.push_back(bindable);
	}

	void DrawableBase::SetIndexBuffer(IndexBuffer* ibuff) noexcept
	{
		_indexBuffer = ibuff;
		_bindables.push_back((IFangBindable*)_indexBuffer);
	}

	void DrawableBase::Update(double deltaTime)
	{
		//do nothing, yet
	}

	void DrawableBase::Draw(FangGraphics& graphics)
	{
		for (auto& bindable : _bindables)
		{
			bindable->Bind(graphics);
		}
		graphics.GetContext()->DrawIndexed(_indexBuffer->GetCount(), 0, 0);
	}
}