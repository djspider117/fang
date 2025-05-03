#pragma once
#include "pch.h"
#include "IFangDrawable.h"

#include <vector>
#include <map>

namespace Fang::Rendering
{
	class BasicMaterial;

	public class GraphicsScene
	{
	public:
		GraphicsScene() = default;
		~GraphicsScene() = default; // TODO, this is leaky

		void AddDrawable(IFangDrawable* drawable);
		void StoreMaterial(const std::wstring& materialName, BasicMaterial* mat);

		void Update(double deltaTime);
		void Draw(FangGraphics& graphics);

	private:
		std::vector<IFangDrawable*> _drawables;
		std::map<std::wstring, BasicMaterial*> _materials;
	};
}
