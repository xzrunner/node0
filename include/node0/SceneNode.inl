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

	ComponentID id = GetComponentTypeID<T>();
	m_component_bitset[id] = true;

	auto itr = m_components.begin();
	for (; itr != m_components.end(); ++itr) {
		if ((*itr)->TypeID() > id) {
			break;
		}
	}
	m_components.insert(itr, std::move(comp_ptr));

//	comp.Init();
	return comp;
}

template <typename T>
T& SceneNode::GetComponent() const
{
	GD_ASSERT(HasComponent<T>(), "no component");
	auto id = GetComponentTypeID<T>();

	int idx = -1;
	int start = 0;
	int end = m_components.size() - 1;
	while (start <= end)
	{
		int mid = (start + end) / 2;
		auto& comp = m_components[mid];
		if (id == comp->TypeID()) {
			idx = mid;
			break;
		} else if (id < comp->TypeID()) {
			end = mid - 1;
		} else {
			start = mid + 1;
		}
	}	
	GD_ASSERT(idx != -1, "err idx");

	return *reinterpret_cast<T*>(m_components[idx].get());
}

}