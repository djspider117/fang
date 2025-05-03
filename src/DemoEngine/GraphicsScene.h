#pragma once
#include "pch.h"
#include "IFangDrawable.h"
#include "Camera.h"

#include <vector>
#include <map>

namespace Fang::Rendering
{
	class BasicMaterial;

	public class GraphicsScene
	{
	public:
		GraphicsScene() = default;
		~GraphicsScene();

		void AddDrawable(IFangDrawable* drawable);
		void StoreMaterial(const std::wstring& materialName, BasicMaterial* mat);

		void Update(double deltaTime);
		void Draw(FangGraphics& graphics);

		inline const Camera* GetCurrentCamera() const noexcept { return _currentCamera; }
		inline void SetCurrentCamera(Camera* currentCamera) noexcept { _currentCamera = currentCamera; }

	private:
		Camera* _currentCamera;

		std::vector<IFangDrawable*> _drawables;
		std::map<std::wstring, BasicMaterial*> _materials;
	};
}
