#pragma once

#include "node0/typedef.h"

#include <cu/cu_macro.h>

#include <map>
#include <vector>
#include <memory>

namespace n0
{

class CompAsset;

class NodePool
{
public:
	using NodeWeakPtr = std::weak_ptr<SceneNode>;
	using NodeArray   = std::vector<NodeWeakPtr>;

public:
	void Add(const std::shared_ptr<CompAsset>& asset, 
		const SceneNodePtr& node);
	const NodeArray* Query(const std::shared_ptr<CompAsset>& asset) const;

private:
	using AssetWeakPtr = std::weak_ptr<CompAsset>;
	using AssetLess    = std::owner_less<AssetWeakPtr>;
	std::map<AssetWeakPtr, NodeArray, AssetLess> m_asset2nodes;

	CU_SINGLETON_DECLARATION(NodePool)

}; // NodePool

}