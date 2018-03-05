#pragma once

#include <memory>
#include <vector>
#include <bitset>
#include <array>
#include <functional>

namespace n0
{

class NodeUniqueComp;
class NodeSharedComp;

class SceneNode
{
public:
	SceneNode() {}
	SceneNode(const SceneNode&);
	SceneNode& operator = (const SceneNode&);

	std::shared_ptr<SceneNode> Clone() const;

	// unique

	template <typename T>
	bool HasUniqueComp() const;

	template <typename T, typename... TArgs>
	T& AddUniqueComp(TArgs&&... args);

	template <typename T>
	T& GetUniqueComp() const;

	void TraverseUniqueComp(std::function<bool(const std::unique_ptr<NodeUniqueComp>&)> func);

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

	void TraverseSharedComp(std::function<bool(const std::shared_ptr<NodeSharedComp>&)> func);
	
private:
	template <typename T>
	static int QueryIndexByID(const std::vector<T>& array, size_t id);

private:
	std::vector<std::unique_ptr<NodeUniqueComp>> m_unique_comp;
	std::vector<std::shared_ptr<NodeSharedComp>> m_shared_comp;

	static const size_t MAX_COMPONENTS = 16;
	std::bitset<MAX_COMPONENTS> m_unique_comp_bitset;
	std::bitset<MAX_COMPONENTS> m_shared_comp_bitset;

}; // SceneNode

}

#include "node0/SceneNode.inl"
