#pragma once
#include "pch.h"
#include "IFangBindable.h"

#include "Topology.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace Fang::Rendering
{
	public class IndexedMesh : public IFangBindable
	{
	public:
		template<typename T>
		IndexedMesh(FangGraphics& gfx, D3D11_PRIMITIVE_TOPOLOGY topo, const T* vertices, UINT verticesSize, const USHORT* indices, UINT indicesSize, UINT indicesCount) :
			_topology(topo),
			_vbuff(gfx, vertices, verticesSize),
			_ibuff(gfx, indices, indicesSize)
		{
			_ibuff.SetCount(indicesCount);
		}

		~IndexedMesh() = default;

		void Bind(FangGraphics& graphics) noexcept override;
		inline UINT GetIndiciesCount() const { return _ibuff.GetCount(); }
		inline const Bindables::IndexBuffer* GetIndexBufferPointer() const { return &_ibuff; }

	private:
		Bindables::Topology _topology;
		Bindables::VertexBuffer _vbuff;
		Bindables::IndexBuffer _ibuff;
	};
}