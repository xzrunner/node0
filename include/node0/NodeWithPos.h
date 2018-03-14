#pragma once

#include "node0/typedef.h"

namespace n0
{

class NodeWithPos
{
public:
	NodeWithPos();
	NodeWithPos(const SceneNodePtr& node, const SceneNodePtr& root, size_t node_id);

	bool operator == (const NodeWithPos& nwp) const;

	const SceneNodePtr& GetNode() const { return m_node; }
	const SceneNodePtr& GetRoot() const { return m_root; }
	size_t GetNodeID() const { return m_node_id; }

	void Init(const SceneNodePtr& node, const SceneNodePtr& root, size_t node_id);

	void Reset();

private:
	SceneNodePtr m_node;

	SceneNodePtr m_root;
	size_t       m_node_id;

}; // SceneNodePos

}