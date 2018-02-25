#include "node0/SerializeSystem.h"
#include "node0/SceneNode.h"
#include "node0/CompStorer.h"
#include "node0/CompFactory.h"

namespace n0
{

void SerializeSystem::StoreNodeToJson(const n0::SceneNodePtr& node, const std::string& dir,
                                      rapidjson::Value& val, rapidjson::MemoryPoolAllocator<>& alloc)
{
	val.SetObject();

	// tree

	rapidjson::Value val_children;
	val_children.SetArray();

	auto& children = node->GetAllChildren();
	int idx = 0;
	for (auto& child : children) 
	{
		rapidjson::Value cval;
		StoreNodeToJson(child, dir, cval, alloc);
		val_children.PushBack(cval, alloc);
	}

	if (!children.empty()) {
		val.AddMember("children", val_children, alloc);
	}

	// components

	rapidjson::Value val_components;
	val_components.SetObject();

	auto& components = node->GetAllComponents();
	for (auto& comp : components)
	{
		rapidjson::Value cval;
		if (CompStorer::Instance()->ToJson(*comp, dir, cval, alloc)) {
			val_components.AddMember(rapidjson::StringRef(comp->Type()), cval, alloc);
		}
	}

	if (!components.empty()) {
		val.AddMember("components", val_components, alloc);
	}
}

void SerializeSystem::LoadNodeFromJson(n0::SceneNodePtr& node, 
	                                   const std::string& dir,
	                                   const rapidjson::Value& val)
{
	// tree
	if (val.HasMember("children")) 
	{
		for (auto& val_child : val["children"].GetArray()) 
		{
			auto child = std::make_shared<n0::SceneNode>();
			LoadNodeFromJson(child, dir, val_child);
			node->AddChild(child);
			child->SetParent(node);
		}
	}

	// components
	if (val.HasMember("components"))
	{
		auto itr = val["components"].MemberBegin();
		for ( ; itr != val["components"].MemberEnd(); ++itr) {
			CompFactory::Instance()->Create(
				node, itr->name.GetString(), dir, itr->value);
		}
	}
}

}