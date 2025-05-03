#include "pch.h"
#include "GraphicsScene.h"
#include "Material.h"

namespace Fang::Rendering
{
	void GraphicsScene::AddDrawable(IFangDrawable* drawable)
	{
		assert(drawable != nullptr);
		_drawables.push_back(drawable);
	}

	void GraphicsScene::StoreMaterial(const std::wstring& materialName, BasicMaterial* mat)
	{
		_materials.insert({ materialName, mat });
	}

	void GraphicsScene::Update(double deltaTime)
	{
		for (auto& drawable : _drawables)
		{
			drawable->Update(deltaTime);
		}
	}

	void GraphicsScene::Draw(FangGraphics& graphics)
	{
		for (auto& drawable : _drawables)
		{
			drawable->Draw(graphics);
		}
	}

}