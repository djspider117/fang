#pragma once
#include "pch.h"

namespace Fang::Rendering
{
	public interface IFangBindable
	{
		virtual void Bind(FangGraphics& graphics) noexcept = 0;
		virtual ~IFangBindable() = default;
	};
}