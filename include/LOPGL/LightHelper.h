#ifndef LIGHT_HELPER_H
#define LIGHT_HELPER_H

#include "Shader.h"
#include "Light.h"

namespace hdgbdn
{
	void SetDirectLight(Shader& shader, const DirectionalLight& light);
}

#endif