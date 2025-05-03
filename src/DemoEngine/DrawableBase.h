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

		DrawableBase() = default;
		virtual ~DrawableBase() = default;

		virtual void AddBindable(IFangBindable* bindable) noexcept override;

		virtual void SetIndexBuffer(const IndexBuffer* ibuff) noexcept override;

		virtual void Update(double deltaTime) override;

		virtual void Draw(FangGraphics& graphics) override;

		virtual DirectX::XMMATRIX GetTransform() const override
		{
			return DirectX::XMMatrixIdentity();
		}

	protected:
		const IndexBuffer* _indexBuffer = nullptr;
		std::vector<IFangBindable*> _bindables;
	};
}