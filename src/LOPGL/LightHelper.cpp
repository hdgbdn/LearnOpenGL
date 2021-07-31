#include "LightHelper.h"

using namespace hdgbdn;

void hdgbdn::SetDirectLight(Shader& shader, const DirectionalLight& light)
{
    shader.set("light.direction", light.getDirection());
    shader.set("light.ambient", light.getColor());
    shader.set("light.diffuse", light.getColor());
    shader.set("light.specular", light.getColor());
}