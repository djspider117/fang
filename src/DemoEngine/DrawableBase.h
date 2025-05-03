#pragma once
#include "IFangDrawable.h"
#include <vector>
#include <memory>
#include "IFangBindable.h"
#include "IndexBuffer.h"

using namespace Fang::Rendering::Bindables;

namespace Fang::Rendering::Drawables
{
	public class DrawableBase : public IFangDrawable
	{
	public:
		DrawableBase(const DrawableBase&) = delete;

		DrawableBase() : _transform(DirectX::XMMatrixIdentity()) {}
		DrawableBase(XMMATRIX transform) :
			_transform(transform)
		{
		}

		virtual void AddBindable(IFangBindable* bindable) noexcept override;

		virtual void SetIndexBuffer(IndexBuffer* ibuff) noexcept override;

		virtual void Update(double deltaTime) override;

		virtual void Draw(FangGraphics& graphics) override;

		virtual DirectX::XMMATRIX GetTransform() override
		{
			// const ref?
			return _transform;
		}

	protected:
		const IndexBuffer* _indexBuffer = nullptr;
		std::vector<IFangBindable*> _bindables;
		XMMATRIX _transform;
	};

	HRESULT CreateDemoDrawable(FangGraphics& gfx, IFangDrawable** ppDrawable);
}