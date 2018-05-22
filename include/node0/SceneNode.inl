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

	return (m.unique_comp_bitset & (1 << GetUniqueCompTypeID<T>())) != 0;
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
	GD_ASSERT(id < MAX_UNIQUE_COMPONENTS, "too many components");
	m.unique_comp_bitset |= (1 << id);

	auto new_unique_comp_sz = m.unique_comp_sz + 1;
	auto new_unique_comp = new std::unique_ptr<NodeUniqueComp>[new_unique_comp_sz];
	bool added = false;
	int ptr_new = 0, ptr_old = 0;
	for (size_t i = 0; i < m.unique_comp_sz; ++i)
	{
		GD_ASSERT(m_unique_comp[i]->TypeID() != id, "exists");
		if (m_unique_comp[i]->TypeID() < id) {
			new_unique_comp[ptr_new++] = std::move(m_unique_comp[ptr_old++]);
		} else {
			added = true;
			new_unique_comp[ptr_new++] = std::move(comp_ptr);
			while (i++ < m.unique_comp_sz) {
				new_unique_comp[ptr_new++] = std::move(m_unique_comp[ptr_old++]);
			}
			break;
		}
	}
	if (!added) {
		new_unique_comp[ptr_new++] = std::move(comp_ptr);
	}
	m.unique_comp_sz = new_unique_comp_sz;
	delete[] m_unique_comp;
	m_unique_comp = new_unique_comp;

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

	int idx = QueryIndexByID<std::unique_ptr<NodeUniqueComp>>(m_unique_comp, m.unique_comp_sz, id);
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
		if ((m.shared_comp_bitset & (1 << id)) == 0) {
			return false;
		} else if (std::is_same<T, CompAsset>::value) {
			return true;
		} else {
			int idx = QueryIndexByID<std::shared_ptr<NodeSharedComp>>(m_shared_comp, m.shared_comp_sz, id);
			auto& comp = *reinterpret_cast<T*>(m_shared_comp[idx].get());
			return comp.AssetTypeID() == GetAssetUniqueTypeID<T>();
		}
	}
	else
	{
		return (m.shared_comp_bitset & (1 << GetSharedCompTypeID<T>())) != 0;
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
	GD_ASSERT(id < MAX_SHARED_COMPONENTS, "too many components");
	m.shared_comp_bitset |= (1 << id);

	auto new_shared_comp_sz = m.shared_comp_sz + 1;
	auto new_shared_comp = new std::shared_ptr<NodeSharedComp>[new_shared_comp_sz];
	bool added = false;
	int ptr_new = 0, ptr_old = 0;
	for (size_t i = 0; i < m.shared_comp_sz; ++i)
	{
		GD_ASSERT(m_shared_comp[i]->TypeID() != id, "exists");
		if (m_shared_comp[i]->TypeID() < id) {
			new_shared_comp[ptr_new++] = m_shared_comp[ptr_old++];
		} else {
			added = true;
			new_shared_comp[ptr_new++] = comp_ptr;
			while (i++ < m.shared_comp_sz) {
				new_shared_comp[ptr_new++] = m_shared_comp[ptr_old++];
			}
			break;
		}
	}
	if (!added) {
		new_shared_comp[ptr_new++] = comp_ptr;
	}
	m.shared_comp_sz = new_shared_comp_sz;
	delete[] m_shared_comp;
	m_shared_comp = new_shared_comp;

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
	GD_ASSERT(id < MAX_SHARED_COMPONENTS, "too many components");
	m.shared_comp_bitset |= (1 << id);

	auto new_shared_comp_sz = m.shared_comp_sz + 1;
	auto new_shared_comp = new std::shared_ptr<NodeSharedComp>[new_shared_comp_sz];
	bool added = false;
	int ptr_new = 0, ptr_old = 0;
	for (size_t i = 0; i < m.shared_comp_sz; ++i)
	{
		GD_ASSERT(m_shared_comp[i]->TypeID() != id, "exists");
		if (m_shared_comp[i]->TypeID() < id) {
			new_shared_comp[ptr_new++] = m_shared_comp[ptr_old++];
		} else {
			added = true;
			new_shared_comp[ptr_new++] = comp;
			while (i++ < m.shared_comp_sz) {
				new_shared_comp[ptr_new++] = m_shared_comp[ptr_old++];
			}
			break;
		}
	}
	if (!added) {
		new_shared_comp[ptr_new++] = comp;
	}
	m.shared_comp_sz = new_shared_comp_sz;
	delete[] m_shared_comp;
	m_shared_comp = new_shared_comp;
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

	int idx = QueryIndexByID<std::shared_ptr<NodeSharedComp>>(m_shared_comp, m.shared_comp_sz, id);
	return std::static_pointer_cast<T>(m_shared_comp[idx]);
}

template <typename T>
int SceneNode::QueryIndexByID(const T* array, size_t array_sz, size_t id)
{
	int idx = -1;
	int start = 0;
	int end = array_sz - 1;
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