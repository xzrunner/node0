#pragma once

#include "node0/typedef.h"

#include <rapidjson/document.h>

namespace n0
{

class SerializeSystem
{
public:
	static void StoreNodeToJson(const n0::SceneNodePtr& node, const std::string& dir, 
		rapidjson::Value& val, rapidjson::MemoryPoolAllocator<>& alloc);
	static void LoadNodeFromJson(n0::SceneNodePtr& node, const std::string& dir,
		const rapidjson::Value& val);

}; // SerializeSystem

}