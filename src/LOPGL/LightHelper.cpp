#include "LightHelper.h"
#include <string>

using namespace hdgbdn;

void hdgbdn::SetDirectLight(Shader& shader, const DirectionalLight& light)
{
    shader.set("dirLight.direction", light.getDirection());
    shader.set("dirLight.ambient", light.getAmbient());
    shader.set("dirLight.diffuse", light.getDiffuse());
    shader.set("dirLight.specular", light.getSpecular());
}

void hdgbdn::SetPointLight(Shader& shader, const PointLight& light, int i)
{
    shader.set("pointLights[" + std::to_string(i) + "].position", light.getPosition());
    shader.set("pointLights[" + std::to_string(i) + "].ambient", light.getAmbient());
    shader.set("pointLights[" + std::to_string(i) + "].diffuse", light.getDiffuse());
    shader.set("pointLights[" + std::to_string(i) + "].specular", light.getSpecular());
    shader.set("pointLights[" + std::to_string(i) + "].constant", light.getKC());
    shader.set("pointLights[" + std::to_string(i) + "].linear", light.getKL());
    shader.set("pointLights[" + std::to_string(i) + "].quadratic", light.getKQ());
}