#pragma once

#include <rapidjson/document.h>

#include <memory>

#include <boost/noncopyable.hpp>

namespace n0
{

using ComponentID = size_t;

namespace Internal
{
inline ComponentID GetUniqueComponentID() noexcept
{
    static ComponentID id{0u};
    return id++;
}
}

template <typename T>
inline ComponentID GetComponentTypeID() noexcept
{
    static_assert(std::is_base_of<NodeComponent, T>::value,
        "T must inherit from Component");

    static ComponentID type_id{Internal::GetUniqueComponentID()};
    return type_id;
}

class NodeComponent : boost::noncopyable
{
public:
	virtual ~NodeComponent() {}

	virtual const char* Type() const = 0;
	virtual n0::ComponentID TypeID() const = 0;
	virtual std::unique_ptr<NodeComponent> Clone() const = 0;

}; // NodeComponent

}