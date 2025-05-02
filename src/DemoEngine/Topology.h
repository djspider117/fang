#pragma once
#include "IFangBindable.h"

namespace Fang::Rendering::Bindables
{
	public class Topology : public IFangBindable
	{
	public:
		Topology(D3D11_PRIMITIVE_TOPOLOGY topology) :
			_topology(topology)
		{
			
		}

		virtual void Bind(FangGraphics& graphics) noexcept override
		{
			graphics.GetContext()->IASetPrimitiveTopology(_topology);
		}

	private:
		D3D11_PRIMITIVE_TOPOLOGY _topology;
	};
}