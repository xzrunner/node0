#pragma once

#include "node0/NodeComponent.h"
#include "node0/typedef.h"

#include <vector>

namespace n0
{

class CompComplex : public NodeComponent
{
public:
	virtual const char* Type() const override { return TYPE_NAME; }

	void AddChild(const std::shared_ptr<SceneNode>& child);
	bool RemoveChild(const std::shared_ptr<SceneNode>& child);

	const std::vector<SceneNodePtr>& GetAllChildren() const {
		return m_children;
	}
	void SetChildren(const std::vector<SceneNodePtr>& children) {
		m_children = children;
	}

	static const char* const TYPE_NAME;

private:
	std::vector<SceneNodePtr> m_children;

}; // CompComplex

}