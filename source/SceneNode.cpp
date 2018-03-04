#include "node0/SceneNode.h"

namespace n0
{

SceneNode::SceneNode(const SceneNode& node)
	: m_component_bitset(node.m_component_bitset)
	, m_component_array(node.m_component_array)
{
	m_components.reserve(node.m_components.size());
	for (auto& comp : node.m_components) {
		m_components.push_back(comp->Clone());
	}
}

SceneNode& SceneNode::operator = (const SceneNode& node)
{
	if (this == &node) {
		return *this;
	}

	m_components.clear();
	m_components.reserve(node.m_components.size());
	for (auto& comp : node.m_components) {
		m_components.push_back(comp->Clone());
	}

	m_component_bitset = node.m_component_bitset;
	m_component_array = node.m_component_array;

	return *this;
}

std::shared_ptr<SceneNode> SceneNode::Clone() const
{
	return std::make_shared<SceneNode>(*this);
}

}