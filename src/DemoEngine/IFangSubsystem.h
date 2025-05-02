#pragma once

#include "pch.h"

namespace Fang::Core
{
	public interface IFangSubsystem
	{
		virtual HRESULT Start() = 0;
		virtual HRESULT Stop() = 0;
	};
}