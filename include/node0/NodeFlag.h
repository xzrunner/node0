#pragma once

namespace n0
{

using FlagID = size_t;

namespace Internal
{
inline size_t GetFlagID() noexcept
{
	static FlagID id{ 0u };
	return id++;
}
}

class NodeFlagType
{
}; // NodeFlagType

template <typename T>
inline FlagID GetFlagTypeID() noexcept
{
	static_assert(std::is_base_of<NodeFlagType, T>::value,
		"T must inherit from NodeFlagType");

	static FlagID type_id{ Internal::GetFlagID() };
	return type_id;
}

}