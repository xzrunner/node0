#include "node0/CompIdentity.h"

#include <string>

namespace n0
{

const char* const CompIdentity::TYPE_NAME = "n0_identity";

CompIdentity::CompIdentity()
	: m_id(0)
{
}

std::unique_ptr<n0::NodeUniqueComp> CompIdentity::Clone(const n0::SceneNode& obj) const
{
	auto comp = std::make_unique<CompIdentity>();
	comp->m_filepath = m_filepath;
	comp->m_name     = m_name;
	return comp;
}

}