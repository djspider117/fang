#pragma once
#include "IFangSubsystem.h"

using namespace Fang::Core;

namespace Fang::Input
{
	public class FangInput : public IFangSubsystem
	{
	public:
		virtual HRESULT Start() override { return S_OK; }
		virtual HRESULT Stop() override { return S_OK; }
	};
}