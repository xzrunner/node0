#pragma once

#include <boost/noncopyable.hpp>

#include <memory>

namespace n0
{

using UniqueCompID = size_t;

namespace Internal
{

inline size_t GetUniqueCompID() noexcept
{
    static UniqueCompID id{ 0u };
    return id++;
}

}

template <typename T>
inline UniqueCompID GetUniqueCompTypeID() noexcept
{
    static_assert(std::is_base_of<NodeUniqueComp, T>::value,
        "T must inherit from Component");

    static UniqueCompID type_id{Internal::GetUniqueCompID()};
    return type_id;
}

class NodeUniqueComp : boost::noncopyable
{
public:
	virtual ~NodeUniqueComp() {}

	virtual const char* Type() const = 0;
	virtual UniqueCompID TypeID() const = 0;
	virtual std::unique_ptr<NodeUniqueComp> Clone() const = 0;

}; // NodeUniqueComp

}