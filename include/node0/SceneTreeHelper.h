#pragma once

#include "node0/typedef.h"

#include <vector>

namespace n0
{

class SceneTreeHelper
{
public:
	static void GetPathToRoot(const SceneNodePtr& root, size_t end_id, 
		std::vector<SceneNodePtr>& path);

}; // SceneTreeHelper

}