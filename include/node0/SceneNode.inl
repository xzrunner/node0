#pragma once

#include "node0/NodeComponent.h"

#include <guard/check.h>

namespace n0
{

template <typename T>
bool SceneNode::HasComponent() const 
{
	return m_component_bitset[GetComponentTypeID<T>()];
}

template <typename T, typename... TArgs>
T& SceneNode::AddComponent(TArgs&&... args)
{
	GD_ASSERT(!HasComponent<T>(), "already has the component");

	auto comp_ptr = std::make_unique<T>(std::forward<TArgs>(args)...);
	auto& comp = *comp_ptr;

	m_component_bitset[GetComponentTypeID<T>()] = true;
	m_components.insert(
		std::upper_bound(m_components.begin(), m_components.end(), comp_ptr, NodeComponentLessThan()),
		std::move(comp_ptr));

//	comp.Init();
	return comp;
}

template <typename T>
T& SceneNode::GetComponent() const
{
	GD_ASSERT(HasComponent<T>(), "no component");
	auto id = GetComponentTypeID<T>();

	auto itr = std::upper_bound(m_components.begin(), m_components.end(), id, NodeComponentLessThan());
//	GD_ASSERT(itr != m_components.end(), "err idx");

	auto ptr(itr->get());
	return *reinterpret_cast<T*>(ptr);
}

}