#include "node0/CompFactory.h"
#include "node0/SceneNode.h"

namespace n0
{

CU_SINGLETON_DEFINITION(CompFactory);

CompFactory::CompFactory()
{
}

void CompFactory::Create(n0::SceneNodePtr& node, 
	                     const std::string& name, 
	                     const std::string& dir,
	                     const rapidjson::Value& val) const
{
	auto itr = m_creator.find(name);
	if (itr != m_creator.end()) {
		itr->second(node, dir, val);
	} else {
		GD_REPORT_ASSERT("no comp creator");
	}
}

void CompFactory::AddCreator(const std::string& name, const CreateFunc& func)
{
	auto status = m_creator.insert(std::make_pair(name, func));
	GD_ASSERT(status.second, "duplicate.");
}

}