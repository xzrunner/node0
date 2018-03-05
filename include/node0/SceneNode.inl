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

	int idx = QueryIndexByID<std::unique_ptr<NodeUniqueComp>>(m_unique_comp, id);
	return *reinterpret_cast<T*>(m_unique_comp[idx].get());
}

// shared

template <typename T>
bool SceneNode::HasSharedComp() const
{
	static_assert(std::is_base_of<NodeSharedComp, T>::value,
		"T must inherit from NodeSharedComp");

	if (std::is_base_of<CompAsset, T>::value) 
	{
		auto id = GetSharedCompTypeID<CompAsset>();
		if (!m_shared_comp_bitset[id]) {
			return false;
		} else if (std::is_same<T, CompAsset>::value) {
			return true;
		} else {
			int idx = QueryIndexByID<std::shared_ptr<NodeSharedComp>>(m_shared_comp, id);
			auto& comp = *reinterpret_cast<T*>(m_shared_comp[idx].get());
			return comp.AssetTypeID() == GetAssetUniqueTypeID<T>();
		}
	}
	else
	{
		return m_shared_comp_bitset[GetSharedCompTypeID<T>()];
	}
}

template <typename T, typename... TArgs>
T& SceneNode::AddSharedComp(TArgs&&... args)
{
	static_assert(std::is_base_of<NodeSharedComp, T>::value,
		"T must inherit from NodeSharedComp");

	GD_ASSERT(!HasSharedComp<T>(), "already has the component");

	auto comp_ptr = std::make_shared<T>(std::forward<TArgs>(args)...);
	auto& comp = *comp_ptr;

	SharedCompID id = std::is_base_of<CompAsset, T>::value ? 
		GetSharedCompTypeID<CompAsset>() : GetSharedCompTypeID<T>();
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
void SceneNode::AddSharedCompNoCreate(const std::shared_ptr<T>& comp)
{
	static_assert(std::is_base_of<NodeSharedComp, T>::value,
		"T must inherit from NodeSharedComp");

	GD_ASSERT(!HasSharedComp<T>(), "already has the component");

	SharedCompID id = std::is_base_of<CompAsset, T>::value ? 
		GetSharedCompTypeID<CompAsset>() : GetSharedCompTypeID<T>();
	m_shared_comp_bitset[id] = true;

	auto itr = m_shared_comp.begin();
	for (; itr != m_shared_comp.end(); ++itr) {
		if ((*itr)->TypeID() > id) {
			break;
		}
	}
	m_shared_comp.insert(itr, comp);
}

template <typename T>
T& SceneNode::GetSharedComp() const
{
	return *reinterpret_cast<T*>(GetSharedCompPtr<T>().get());
}

template <typename T>
std::shared_ptr<T> SceneNode::GetSharedCompPtr() const
{
	static_assert(std::is_base_of<NodeSharedComp, T>::value,
		"T must inherit from NodeSharedComp");

	GD_ASSERT(HasSharedComp<T>(), "no component");
	SharedCompID id = std::is_base_of<CompAsset, T>::value ?
		GetSharedCompTypeID<CompAsset>() : GetSharedCompTypeID<T>();

	int idx = QueryIndexByID<std::shared_ptr<NodeSharedComp>>(m_shared_comp, id);
	return std::static_pointer_cast<T>(m_shared_comp[idx]);
}

template <typename T>
int SceneNode::QueryIndexByID(const std::vector<T>& array, size_t id)
{
	int idx = -1;
	int start = 0;
	int end = array.size() - 1;
	while (start <= end)
	{
		int mid = (start + end) / 2;
		auto& comp = array[mid];
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
	return idx;
}

}