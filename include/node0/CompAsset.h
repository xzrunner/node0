#pragma once

#include "node0/NodeComp.h"
#include "node0/typedef.h"

#include <functional>

namespace n0
{

using AssetID = size_t;

namespace Internal
{
inline size_t GetUniqueAssetID() noexcept
{
	static AssetID id{ 0u };
	return id++;
}
}

template <typename T>
inline AssetID GetAssetUniqueTypeID() noexcept
{
	static_assert(std::is_base_of<CompAsset, T>::value,
		"T must inherit from CompAsset");

	static AssetID type_id{ Internal::GetUniqueAssetID() };
	return type_id;
}

class CompAsset : public NodeComp
{
public:
	CompAsset() : m_node_count(1) {}

	virtual n0::CompID TypeID() const override {
		return GetCompTypeID<CompAsset>();
	}
	virtual std::unique_ptr<NodeComp> Clone(const SceneNode& node) const { return nullptr; }

	virtual AssetID AssetTypeID() const = 0;

	virtual void Traverse(std::function<bool(const SceneNodePtr&)> func,
		bool inverse = false) const = 0;

	size_t GetNodeCount() const { return m_node_count; }

protected:
	mutable size_t m_node_count;

}; // CompAsset

}