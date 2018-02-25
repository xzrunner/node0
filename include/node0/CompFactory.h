#pragma once

#include "node0/typedef.h"

#include <cu/cu_macro.h>

#include <rapidjson/document.h>

#include <functional>
#include <map>

namespace n0
{

class CompFactory
{
public:
	using CreateFunc = std::function<void(n0::SceneNodePtr&, const std::string&, const rapidjson::Value&)>;

	void Create(n0::SceneNodePtr& node, const std::string& name, 
		const std::string& dir, const rapidjson::Value& val) const;

	void AddCreator(const std::string& name, const CreateFunc& func);

private:
	std::map<std::string, CreateFunc> m_creator;

	CU_SINGLETON_DECLARATION(CompFactory);

}; // CompFactory

}