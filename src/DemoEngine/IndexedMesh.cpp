#include "pch.h"
#include "IndexedMesh.h"

void Fang::Rendering::IndexedMesh::Bind(FangGraphics& graphics) noexcept
{
	_topology.Bind(graphics);
	_vbuff.Bind(graphics);
	_ibuff.Bind(graphics);
}
