#include "node0/NodePool.h"

namespace n0
{

CU_SINGLETON_DEFINITION(NodePool)

NodePool::NodePool()
{
}

void NodePool::Add(const std::shared_ptr<CompAsset>& asset, 
	               const SceneNodePtr& node)
{
	auto itr = m_asset2nodes.find(asset);
	if (itr == m_asset2nodes.end())
	{
		std::vector<NodeWeakPtr> nodes;
		nodes.push_back(node);
		m_asset2nodes.insert(std::make_pair(asset, nodes));
	}
	else
	{
		itr->second.push_back(node);
	}
}

const NodePool::NodeArray* 
NodePool::Query(const std::shared_ptr<CompAsset>& asset) const
{
	auto itr = m_asset2nodes.find(asset);
	if (itr == m_asset2nodes.end()) {
		return nullptr;
	} else {
		return &itr->second;
	}
}

}