#pragma once

#include "node0/CompAsset.h"
#include "node0/typedef.h"

#include <vector>
#include <functional>

namespace n0
{

class CompComplex : public CompAsset
{
public:
	virtual const char* Type() const override { return TYPE_NAME; }

	virtual AssetID AssetTypeID() const override {
		return GetAssetUniqueTypeID<CompComplex>();
	}
	virtual void Traverse(std::function<bool(const SceneNodePtr&)> func,
		bool inverse = false) const override;

	void AddChild(const std::shared_ptr<SceneNode>& child);
	bool RemoveChild(const std::shared_ptr<SceneNode>& child);
	void RemoveAllChildren();

	const std::vector<SceneNodePtr>& GetAllChildren() const {
		return m_children;
	}
	void SetChildren(const std::vector<SceneNodePtr>& children);

	static const char* const TYPE_NAME;

protected:
	std::vector<SceneNodePtr> m_children;

}; // CompComplex

}