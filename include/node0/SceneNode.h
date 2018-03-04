#pragma once

#include "node0/NodeComponent.h"

#include <memory>
#include <vector>
#include <bitset>
#include <array>

namespace n0
{

class SceneNode
{
public:
	SceneNode() {}
	SceneNode(const SceneNode&);
	SceneNode& operator = (const SceneNode&);

	std::shared_ptr<SceneNode> Clone() const;

	template <typename T>
	bool HasComponent() const;

	template <typename T, typename... TArgs>
	T& AddComponent(TArgs&&... args);

	template <typename T>
	T& GetComponent() const;

	const std::vector<std::unique_ptr<NodeComponent>>& GetAllComponents() const {
		return m_components;
	}

private:
	

private:
	std::vector<std::unique_ptr<NodeComponent>> m_components;

	static const size_t MAX_COMPONENTS = 32;
	std::bitset<MAX_COMPONENTS> m_component_bitset;

}; // SceneNode

}

#include "node0/SceneNode.inl"
