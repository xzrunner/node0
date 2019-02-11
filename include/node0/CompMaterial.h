#pragma once

#include <painting0/Material.h>
#include <node0/NodeComp.h>

namespace n0
{

class CompMaterial : public NodeComp
{
public:
    virtual const char* Type() const override { return TYPE_NAME; }
    virtual CompID TypeID() const override {
        return GetCompTypeID<CompMaterial>();
    }
    virtual std::unique_ptr<NodeComp> Clone(const SceneNode& node) const override;

    void  SetMaterial(std::unique_ptr<pt0::Material>& material);
    auto& GetMaterial() const { return m_material; }

    static const char* const TYPE_NAME;

private:
	std::unique_ptr<pt0::Material> m_material = nullptr;

}; // CompMaterial

}