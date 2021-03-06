#include "node0/CompComplex.h"
#include "node0/SceneNode.h"

namespace n0
{

const char* const CompComplex::TYPE_NAME = "n0_complex";

//std::shared_ptr<NodeComponent> CompComplex::Clone() const
//{
//	auto comp = std::make_shared<CompComplex>();
//	comp->m_children.reserve(m_children.size());
//	for (auto& child : m_children) {
//		comp->m_children.push_back(child->Clone());
//	}
//	return comp;
//}

void CompComplex::Traverse(std::function<bool(const SceneNodePtr&)> func, bool inverse) const
{
	if (inverse)
	{
		for (auto& itr = m_children.rbegin(); itr != m_children.rend(); ++itr) {
			if (!func(*itr)) {
				break;
			}
		}
	}
	else
	{
		for (auto& child : m_children) {
			if (!func(child)) {
				break;
			}
		}
	}
}

void CompComplex::AddChild(const std::shared_ptr<SceneNode>& child)
{
	m_children.push_back(child);

	if (child->HasSharedComp<CompAsset>()) {
		auto& casset = child->GetSharedComp<CompAsset>();
		m_node_count += casset.GetNodeCount();
	}
}

bool CompComplex::RemoveChild(const std::shared_ptr<SceneNode>& child)
{
	for (auto itr = m_children.begin(); itr != m_children.end(); ++itr)
	{
		if (*itr == child)
		{
			m_children.erase(itr);

			if (child->HasSharedComp<CompAsset>()) {
				auto& casset = child->GetSharedComp<CompAsset>();
				m_node_count -= casset.GetNodeCount();
			}

			return true;
		}
	}
	return false;
}

void CompComplex::RemoveAllChildren()
{
	m_children.clear();
	m_node_count = 1;
}

void CompComplex::SetChildren(const std::vector<SceneNodePtr>& children)
{
	m_children = children;

	for (auto& child : children) {
		if (child->HasSharedComp<CompAsset>()) {
			auto& casset = child->GetSharedComp<CompAsset>();
			m_node_count += casset.GetNodeCount();
		}
	}
}

}