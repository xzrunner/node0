#pragma once

#include <boost/noncopyable.hpp>

namespace n0
{

using SharedCompID = size_t;

namespace Internal
{

inline size_t GetSharedCompID() noexcept
{
	static SharedCompID id{ 0u };
	return id++;
}

}

template <typename T>
inline SharedCompID GetSharedCompTypeID() noexcept
{
	static_assert(std::is_base_of<NodeSharedComp, T>::value,
		"T must inherit from Component");

	static SharedCompID type_id{ Internal::GetSharedCompID() };
	return type_id;
}

class NodeSharedComp : boost::noncopyable
{
public:
	virtual ~NodeSharedComp() {}

	virtual const char* Type() const = 0;
	virtual SharedCompID TypeID() const = 0;

}; // NodeSharedComp

}