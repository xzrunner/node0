#pragma once

#include "node0/NodeUniqueComp.h"

#include <guard/check.h>

namespace n0
{

// unique

template <typename T>
bool SceneNode::HasUniqueComp() const
{
	static_assert(std::is_base_of<NodeUniqueComp, T>::value,
		"T must inherit from NodeUniqueComp");

	return m_unique_comp_bitset[GetUniqueCompTypeID<T>()];
}

template <typename T, typename... TArgs>
T& SceneNode::AddUniqueComp(TArgs&&... args)
{
	static_assert(std::is_base_of<NodeUniqueComp, T>::value,
		"T must inherit from NodeUniqueComp");

	GD_ASSERT(!HasUniqueComp<T>(), "already has the component");

	auto comp_ptr = std::make_unique<T>(std::forward<TArgs>(args)...);
	auto& comp = *comp_ptr;

	UniqueCompID id = GetUniqueCompTypeID<T>();
	m_unique_comp_bitset[id] = true;

	auto itr = m_unique_comp.begin();
	for (; itr != m_unique_comp.end(); ++itr) {
		if ((*itr)->TypeID() > id) {
			break;
		}
	}
	m_unique_comp.insert(itr, std::move(comp_ptr));

//	comp.Init();
	return comp;
}

template <typename T>
T& SceneNode::GetUniqueComp() const
{
	static_assert(std::is_base_of<NodeUniqueComp, T>::value,
		"T must inherit from NodeUniqueComp");

	GD_ASSERT(HasUniqueComp<T>(), "no component");
	auto id = GetUniqueCompTypeID<T>();

	int idx = -1;
	int start = 0;
	int end = m_unique_comp.size() - 1;
	while (start <= end)
	{
		int mid = (start + end) / 2;
		auto& comp = m_unique_comp[mid];
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

	return *reinterpret_cast<T*>(m_unique_comp[idx].get());
}

// shared

template <typename T>
bool SceneNode::HasSharedComp() const
{
	static_assert(std::is_base_of<NodeSharedComp, T>::value,
		"T must inherit from NodeSharedComp");

	return m_shared_comp_bitset[GetSharedCompTypeID<T>()];
}

template <typename T, typename... TArgs>
T& SceneNode::AddSharedComp(TArgs&&... args)
{
	static_assert(std::is_base_of<NodeSharedComp, T>::value,
		"T must inherit from NodeSharedComp");

	GD_ASSERT(!HasSharedComp<T>(), "already has the component");

	auto comp_ptr = std::make_shared<T>(std::forward<TArgs>(args)...);
	auto& comp = *comp_ptr;

	SharedCompID id = GetSharedCompTypeID<T>();
	m_shared_comp_bitset[id] = true;

	auto itr = m_shared_comp.begin();
	for (; itr != m_shared_comp.end(); ++itr) {
		if ((*itr)->TypeID() > id) {
			break;
		}
	}
	m_shared_comp.insert(itr, comp_ptr);

//	comp.Init();
	return comp;
}

template <typename T>
T& SceneNode::GetSharedComp() const
{
	static_assert(std::is_base_of<NodeSharedComp, T>::value,
		"T must inherit from NodeSharedComp");

	GD_ASSERT(HasSharedComp<T>(), "no component");
	auto id = GetSharedCompTypeID<T>();

	int idx = -1;
	int start = 0;
	int end = m_shared_comp.size() - 1;
	while (start <= end)
	{
		int mid = (start + end) / 2;
		auto& comp = m_shared_comp[mid];
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

	return *reinterpret_cast<T*>(m_shared_comp[idx].get());
}

}