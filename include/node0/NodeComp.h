#pragma once

#include <boost/noncopyable.hpp>

#include <memory>

namespace n0
{

using CompID = size_t;

namespace Internal
{
inline size_t GetUniqueCompID() noexcept
{
    static CompID id{ 0u };
    return id++;
}
}

template <typename T>
inline CompID GetCompTypeID() noexcept
{
    static_assert(std::is_base_of<NodeComp, T>::value,
        "T must inherit from Component");

    static CompID type_id{Internal::GetUniqueCompID()};
    return type_id;
}

class SceneNode;

class NodeComp : boost::noncopyable
{
public:
	virtual ~NodeComp() {}

	virtual const char* Type() const = 0;
	virtual CompID TypeID() const = 0;
	virtual std::unique_ptr<NodeComp> Clone(const SceneNode& node) const = 0;

}; // NodeComp

}