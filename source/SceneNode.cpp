#include "node0/SceneNode.h"

namespace n0
{

SceneNode::SceneNode(const SceneNode& node)
	: m_shared_comp(node.m_shared_comp)
	, m_unique_comp_bitset(node.m_unique_comp_bitset)
	, m_shared_comp_bitset(node.m_shared_comp_bitset)
{
	m_unique_comp.reserve(node.m_unique_comp.size());
	for (auto& comp : node.m_unique_comp) {
		m_unique_comp.push_back(comp->Clone());
	}
}

SceneNode& SceneNode::operator = (const SceneNode& node)
{
	if (this == &node) {
		return *this;
	}

	m_unique_comp.clear();
	m_unique_comp.reserve(node.m_unique_comp.size());
	for (auto& comp : node.m_unique_comp) {
		m_unique_comp.push_back(comp->Clone());
	}

	m_shared_comp = node.m_shared_comp;

	m_unique_comp_bitset = node.m_unique_comp_bitset;
	m_shared_comp_bitset = node.m_shared_comp_bitset;

	return *this;
}

std::shared_ptr<SceneNode> SceneNode::Clone() const
{
	return std::make_shared<SceneNode>(*this);
}

}