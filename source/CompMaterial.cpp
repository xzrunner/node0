#include "node0/CompMaterial.h"

#include <painting0/Material.h>

namespace n0
{

const char* const CompMaterial::TYPE_NAME = "n0_material";

std::unique_ptr<NodeComp> CompMaterial::Clone(const SceneNode& node) const
{
    auto comp = std::make_unique<CompMaterial>();
    *comp->m_material = *m_material;
    return comp;
}

void CompMaterial::SetMaterial(std::unique_ptr<pt0::Material>& material)
{
    m_material = std::move(material);
}

}