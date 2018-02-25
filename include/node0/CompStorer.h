#pragma once

#include <cu/cu_macro.h>

#include <rapidjson/document.h>

#include <functional>
#include <map>

namespace n0
{

class NodeComponent;

class CompStorer
{
public:
	using ToJsonFunc = std::function<bool(const NodeComponent&, const std::string&, rapidjson::Value&, rapidjson::MemoryPoolAllocator<>&)>;

	bool ToJson(const NodeComponent& comp, const std::string& dir, rapidjson::Value& val, rapidjson::MemoryPoolAllocator<>& alloc) const;
	void AddToJsonFunc(const std::string& name, const ToJsonFunc& func);
	
private:
	std::map<std::string, ToJsonFunc> m_to_json;

	CU_SINGLETON_DECLARATION(CompStorer);

}; // CompStorer

}