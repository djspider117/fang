#include "pch.h"
#include "GraphicsScene.h"
#include "Material.h"

namespace Fang::Rendering
{
	GraphicsScene::~GraphicsScene()
	{
		if (_currentCamera)
			delete _currentCamera;

		for (IFangDrawable* drawable : _drawables)
		{
			delete drawable;
		}

		for (const auto& pair: _materials)
		{
			delete pair.second;
		}
	}
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