#pragma once

#include "node0/typedef.h"

namespace n0
{

class NodeWithPos
{
public:
	SceneNodePtr node;

	SceneNodePtr root;
	size_t       node_id;

public:
	NodeWithPos() : node(nullptr), root(nullptr), node_id(0) {}
	NodeWithPos(const SceneNodePtr& node, const SceneNodePtr& root, size_t node_id)
		: node(node), root(root), node_id(node_id) {}

	bool operator == (const NodeWithPos& nwp) const
	{
		return node == nwp.node
			&& root == nwp.root
			&& node_id == nwp.node_id;
	}
	
}; // SceneNodePos

}