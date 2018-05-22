#pragma once

#include "node0/SceneNode.h"
#include "node0/CompFlags.h"

namespace n0
{

class NodeFlagsHelper
{
public:
	template <typename T>
	static bool GetFlag(const SceneNode& node)
	{
		if (node.HasUniqueComp<CompFlags>()) {
			return node.GetUniqueComp<CompFlags>().GetFlag<T>();
		} else {
			return false;
		}
	}

	template <typename T>
	static void SetFlag(const SceneNode& node, bool flag)
	{
		auto& cflags =
			node.HasUniqueComp<CompFlags>() ?
			node.GetUniqueComp<CompFlags>() :
			const_cast<SceneNode&>(node).AddUniqueComp<CompFlags>();
		cflags.SetFlag<T>(flag);
	}

}; // NodeFlagsHelper

}