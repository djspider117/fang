#pragma once

#include "pch.h"

namespace Fang::Rendering
{
	struct BlindVertex
	{
		struct {
			float X, Y, Z;
		} Position;

		static const D3D11_INPUT_ELEMENT_DESC InputLayoutElements[];
	};

	struct ColoredVertex
	{
		struct {
			float X, Y, Z;
		} Position;
		struct {
			byte R, G, B, A;
		} VertexColor;

		static const D3D11_INPUT_ELEMENT_DESC InputLayoutElements[];
	};

	struct VertexUV
	{
		struct {
			float X, Y, Z;
		} Position;
		struct {
			float u, v;
		} UV;

		static const D3D11_INPUT_ELEMENT_DESC InputLayoutElements[];
	};

	struct ColoredVertexUV
	{
		struct {
			float X, Y, Z;
		} Position;
		struct {
			byte R, G, B, A;
		} VertexColor;
		struct {
			float u, v;
		} UV;

		static const D3D11_INPUT_ELEMENT_DESC InputLayoutElements[];
	};
}