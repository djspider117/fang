#pragma once

#include "pch.h"

namespace Fang::Rendering
{
	struct Vertex
	{
		float X;
		float Y;
		float Z;

		byte R;
		byte G;
		byte B;
		byte A;
	};

	struct ConstantBuffer
	{
		DirectX::XMMATRIX transform;
	};
}