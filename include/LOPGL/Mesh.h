#ifndef MESH_H_
#define MESH_H_

#include <string>
#include <vector>
#include "Shader.h"
#include "Texture.h"
#include "glm/glm.hpp"

using namespace std;

namespace hdgbdn
{
    struct Vertex
    {
        glm::vec3 Position;
        glm::vec3 Normal;
        glm::vec2 UV;
        glm::vec3 Tangent;
        glm::vec3 Bitangent;
    };
	
    class Mesh
    {
    public:
        Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);

        void Draw(Shader& shader);
        void DrawInstances(Shader& shader, int count);
    private:
        unsigned int VAO, VBO, EBO;
        vector<Vertex> vertices;
        vector<unsigned int> indices;
        vector<Texture> textures;
        void setUpMesh();
    };
}

#endif