#pragma once

#include "node0/NodeSharedComp.h"
#include "node0/typedef.h"

#include <SM_Rect.h>

#include <functional>

namespace n0
{

using AssetID = size_t;

namespace Internal
{
inline size_t GetUniqueAssetID() noexcept
{
	static AssetID id{ 0u };
	return id++;
}
}

template <typename T>
inline AssetID GetAssetUniqueTypeID() noexcept
{
	static_assert(std::is_base_of<CompAsset, T>::value,
		"T must inherit from CompAsset");

	static AssetID type_id{ Internal::GetUniqueAssetID() };
	return type_id;
}

class CompAsset : public NodeSharedComp
{
public:
	virtual n0::SharedCompID TypeID() const override {
		return GetSharedCompTypeID<CompAsset>();
	}
	
	virtual AssetID AssetTypeID() const = 0;

	virtual void Traverse(std::function<bool(const SceneNodePtr&)> func) const = 0;

	virtual sm::rect GetBounding() const = 0;

}; // CompAsset

}