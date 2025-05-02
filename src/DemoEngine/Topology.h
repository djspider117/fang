#pragma once
#include "IFangBindable.h"

namespace Fang::Rendering
{
	public class Topology : public IFangBindable
	{
		Topology(D3D11_PRIMITIVE_TOPOLOGY topology) :
			_topology(topology)
		{
			
		}

		virtual void Bind(FangGraphics& graphics) noexcept override
		{
			graphics.GetDeviceContext()->IASetPrimitiveTopology(_topology);
		}

	private:
		D3D11_PRIMITIVE_TOPOLOGY _topology;
	};
}