#include "node0/SceneNode.h"

namespace n0
{

SceneNode::SceneNode()
{
}

SceneNode::SceneNode(const SceneNode& node)
{
	CopyFrom(node);
}

SceneNode& SceneNode::operator = (const SceneNode& node)
{
	CopyFrom(node);
	return *this;
}

SceneNode::~SceneNode()
{
	Clear();
}

std::shared_ptr<SceneNode> SceneNode::Clone() const
{
	return std::make_shared<SceneNode>(*this);
}

void SceneNode::TraverseUniqueComp(std::function<bool(const std::unique_ptr<NodeUniqueComp>&)> func)
{
	for (size_t i = 0; i < m.unique_comp_sz; ++i) {
		if (!func(m_unique_comp[i])) {
			break;
		}
	}
}

void SceneNode::TraverseSharedComp(std::function<bool(const std::shared_ptr<NodeSharedComp>&)> func)
{
	for (size_t i = 0; i < m.shared_comp_sz; ++i) {
		if (!func(m_shared_comp[i])) {
			break;
		}
	}
}

void SceneNode::Clear()
{
	if (m_unique_comp)
	{
		for (size_t i = 0; i < m.unique_comp_sz; ++i) {
			m_unique_comp[i].reset();
		}
		delete[] m_unique_comp;
		m_unique_comp = nullptr;
	}
	if (m_shared_comp)
	{
		for (size_t i = 0; i < m.shared_comp_sz; ++i) {
			m_shared_comp[i].reset();
		}
		delete[] m_shared_comp;
		m_shared_comp = nullptr;
	}
	m.Clear();
}

void SceneNode::CopyFrom(const SceneNode& node)
{
	if (this == &node) {
		return;
	}

	GD_ASSERT(m_unique_comp == nullptr, "m_unique_comp not null");
	GD_ASSERT(m_shared_comp == nullptr, "m_shared_comp not null");

	m = node.m;
	if (m.unique_comp_sz > 0)
	{
		m_unique_comp = new std::unique_ptr<NodeUniqueComp>[m.unique_comp_sz];
		for (size_t i = 0; i < m.unique_comp_sz; ++i) {
			m_unique_comp[i] = node.m_unique_comp[i]->Clone();
		}
	}
	if (m.shared_comp_sz > 0)
	{
		m_shared_comp = new std::shared_ptr<NodeSharedComp>[m.shared_comp_sz];
		for (size_t i = 0; i < m.shared_comp_sz; ++i) {
			m_shared_comp[i] = node.m_shared_comp[i];
		}
	}
}

}