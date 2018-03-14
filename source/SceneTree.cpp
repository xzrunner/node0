#include "node0/SceneTree.h"
#include "node0/SceneNode.h"
#include "node0/CompAsset.h"

#include <guard/check.h>

namespace n0
{

void SceneTree::GetPathToRoot(const SceneNodePtr& root, size_t end_id,
	                          std::vector<SceneNodePtr>& path)
{
	GD_ASSERT(root, "err roor");

	path.clear();

	if (end_id == 0) {
		path.push_back(root);
		return;
	}

	size_t curr_id = 0;
	auto curr_node = root;
	path.push_back(curr_node);
	while (curr_id != end_id)
	{
		auto& casset = curr_node->GetSharedComp<CompAsset>();
		GD_ASSERT(end_id >= curr_id && end_id < curr_id + casset.GetNodeCount(), "err id");
		curr_id += 1;
		casset.Traverse([&](const SceneNodePtr& node)->bool
		{
			auto& casset = node->GetSharedComp<CompAsset>();
			// find
			if (end_id == curr_id)
			{
				curr_node = node;
				path.push_back(node);
				return false;
			}
			// into
			else if (end_id < curr_id + casset.GetNodeCount()) 
			{
				curr_node = node;
				path.push_back(node);
				return false;
			} 
			// skip
			else 
			{
				curr_id += casset.GetNodeCount();
				return true;
			}
		});
	}
}

}