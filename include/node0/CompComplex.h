#pragma once

#include "node0/CompAsset.h"
#include "node0/typedef.h"

#include <vector>
#include <functional>

namespace n0
{

class CompComplex : public n0::CompAsset
{
public:
	virtual const char* Type() const override { return TYPE_NAME; }

	virtual n0::AssetID AssetTypeID() const override {
		return n0::GetAssetUniqueTypeID<CompComplex>();
	}
	virtual void Traverse(std::function<bool(const n0::SceneNodePtr&)> func,
		bool inverse = false) const override;

	void AddChild(const std::shared_ptr<n0::SceneNode>& child);
	bool RemoveChild(const std::shared_ptr<n0::SceneNode>& child);
	void RemoveAllChildren();

	const std::vector<n0::SceneNodePtr>& GetAllChildren() const {
		return m_children;
	}
	void SetChildren(const std::vector<n0::SceneNodePtr>& children);

	static const char* const TYPE_NAME;

protected:
	std::vector<n0::SceneNodePtr> m_children;

}; // CompComplex

}