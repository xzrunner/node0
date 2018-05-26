#include "node0/CompFlags.h"

#include <string>

namespace n0
{

const char* const CompFlags::TYPE_NAME = "n0_flags";

std::unique_ptr<n0::NodeComp> CompFlags::Clone(const n0::SceneNode& obj) const
{
	auto comp = std::make_unique<CompFlags>();
	comp->m_flags_bitset = m_flags_bitset;
	return comp;
}

}