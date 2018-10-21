#include "node0/NodeWithPos.h"

#include <guard/check.h>

namespace n0
{

NodeWithPos::NodeWithPos()
	: m_node(nullptr), m_root(nullptr), m_node_id(0)
{
}

NodeWithPos::NodeWithPos(const SceneNodePtr& node, const SceneNodePtr& root, size_t node_id)
	: m_node(node), m_root(root), m_node_id(node_id)
{
	GD_ASSERT(node && root, "err");
}

bool NodeWithPos::operator == (const NodeWithPos& nwp) const
{
	return m_node == nwp.m_node
		&& m_root == nwp.m_root
		&& m_node_id == nwp.m_node_id;
}

void NodeWithPos::Init(const SceneNodePtr& node, const SceneNodePtr& root, size_t node_id)
{
	GD_ASSERT(node && root, "err");

	m_node = node;
	m_root = root;
	m_node_id = node_id;
}

void NodeWithPos::Reset()
{
	m_node.reset();
	m_root.reset();
	m_node_id = 0;
}

}