#pragma once

#include <guard/check.h>

namespace n0
{

template <typename T>
bool CompFlags::GetFlag() const
{
	FlagID id = GetFlagTypeID<T>();
	GD_ASSERT(id < MAX_FLAGS, "too many flags.");
	return (m_flags_bitset & (1 << id)) != 0;
}

template <typename T>
void CompFlags::SetFlag(bool flag) const
{
	FlagID id = GetFlagTypeID<T>();
	GD_ASSERT(id < MAX_FLAGS, "too many flags.");
	flag ? (m_flags_bitset |= (1 << id)) : (m_flags_bitset &= ~(1 << id));
}

}