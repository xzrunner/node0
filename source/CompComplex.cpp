#include "node0/CompComplex.h"

namespace n0
{

const char* const CompComplex::TYPE_NAME = "n0_complex";

void CompComplex::Traverse(std::function<bool(const n0::SceneNodePtr&)> func) const
{
	for (auto& child : m_children) {
		func(child);
	}
}

void CompComplex::AddChild(const std::shared_ptr<SceneNode>& child)
{
	m_children.push_back(child);
}

bool CompComplex::RemoveChild(const std::shared_ptr<SceneNode>& child)
{
	for (auto itr = m_children.begin(); itr != m_children.end(); ++itr) 
	{
		if (*itr == child) {
			m_children.erase(itr);
			return true;
		}
	}
	return false;
}

void CompComplex::RemoveAllChildren()
{
	m_children.clear();
}

}