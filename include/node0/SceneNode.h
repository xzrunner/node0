#pragma once

#include "node0/NodeFlag.h"

#include <memory>
#include <vector>
#include <bitset>
#include <array>
#include <functional>

namespace n0
{

class NodeComp;
class NodeComp;

class SceneNode
{
public:
	SceneNode();
	SceneNode(const SceneNode&);
	SceneNode& operator = (const SceneNode&);
	~SceneNode();

	std::shared_ptr<SceneNode> Clone() const;

	// unique

	template <typename T>
	bool HasUniqueComp() const;

	template <typename T, typename... TArgs>
	T& AddUniqueComp(TArgs&&... args);

	template <typename T>
	T& GetUniqueComp() const;

	void TraverseUniqueComp(std::function<bool(const std::unique_ptr<NodeComp>&)> func);

	size_t GetUniqueCompCount() const { return m.unique_comp_sz; }

	// shared

	template <typename T>
	bool HasSharedComp() const;

	template <typename T, typename... TArgs>
	T& AddSharedComp(TArgs&&... args);

	template <typename T>
	void AddSharedCompNoCreate(const std::shared_ptr<T>& comp);

	template <typename T>
	T& GetSharedComp() const;
	template <typename T>
	std::shared_ptr<T> GetSharedCompPtr() const;

	void TraverseSharedComp(std::function<bool(const std::shared_ptr<NodeComp>&)> func);

	size_t GetSharedCompCount() const { return m.shared_comp_sz; }

private:
	template <typename T>
	static int QueryIndexByID(const T* array, size_t array_sz, size_t id);

	void Clear();
	void CopyFrom(const SceneNode& node);

private:
	static const size_t MAX_UNIQUE_COMPONENTS = 21;
	static const size_t MAX_SHARED_COMPONENTS = 4;

	struct M
	{
		M() { Clear(); }

		void Clear() {
			memset(this, 0, sizeof(M));
		}

		uint32_t unique_comp_bitset   : MAX_UNIQUE_COMPONENTS;
		uint32_t shared_comp_bitset   : MAX_SHARED_COMPONENTS;
		uint32_t unique_comp_sz       : 5;
		uint32_t shared_comp_sz       : 2;
	};

	std::unique_ptr<NodeComp>* m_unique_comp = nullptr;
	std::shared_ptr<NodeComp>* m_shared_comp = nullptr;

	M m;

}; // SceneNode

}

#include "node0/SceneNode.inl"
