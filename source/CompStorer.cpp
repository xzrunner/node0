#include "node0/CompStorer.h"
#include "node0/NodeComponent.h"

#include <guard/check.h>

namespace n0
{

CU_SINGLETON_DEFINITION(CompStorer);

CompStorer::CompStorer()
{
}

bool CompStorer::ToJson(const NodeComponent& comp, const std::string& dir, rapidjson::Value& val, rapidjson::MemoryPoolAllocator<>& alloc) const
{
	auto itr = m_to_json.find(comp.Type());
	if (itr != m_to_json.end()) {
		return itr->second(comp, dir, val, alloc);
	} else {
		GD_REPORT_ASSERT("no comp creator");
		return false;
	}
}

void CompStorer::AddToJsonFunc(const std::string& name, const ToJsonFunc& func)
{
	auto status = m_to_json.insert(std::make_pair(name, func));
	GD_ASSERT(status.second, "duplicate.");
}

}