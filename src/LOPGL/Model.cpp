#include "Model.h"
#include <filesystem>
#include <iostream>
#include <queue>
#include "assimp/postprocess.h"

using namespace std;
using namespace hdgbdn;
namespace fs = std::filesystem;

void Model::DeleteModelTree(ModelNode* root)
{
    if (root == nullptr) return;
    else
    {
        for (auto nodePtr : root->children) DeleteModelTree(nodePtr);
        delete root;
    }
}

Model::Model(const std::string& path)
	: root(nullptr), name(), directory(), textureLoaded()
{
    loadModel(path);
}

Model::~Model()
{
    DeleteModelTree(this->root);
}


void Model::loadModel(const string& path) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        cout << "ERROR::ASSIMP::" << importer.GetErrorString() << endl;
        return;
    }
    directory = path.substr(0, path.find_last_of('/'));
    name = scene->mName.C_Str();
    root = processNode(scene->mRootNode, scene);
}

ModelNode* Model::processNode(aiNode* node, const aiScene* scene) {
    if (node->mNumMeshes == 0 && node->mNumChildren == 0) return nullptr;
    ModelNode* root = new ModelNode();
    root->name = node->mName.C_Str();
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        root->meshes.push_back(processMesh(mesh, scene));
    }
    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        ModelNode* child = processNode(node->mChildren[i], scene);
    	if(child != nullptr) root->children.push_back(child);
        
    }
    return root;
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene) {
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex;
        glm::vec3 vector;
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;

        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.Normal = vector;

        if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
        {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.UV = vec;
        }
        else
            vertex.UV = glm::vec2(0.0f, 0.0f);

        vertices.push_back(vertex);
    }
    // process indices
    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    // process material
    if (mesh->mMaterialIndex >= 0) {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        // 1. diffuse maps
        vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE);
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        // 2. specular maps
        vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR);
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
        // 3. normal maps
        std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT);
        textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
        // 4. height maps
        std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT);
        textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
    }
    return Mesh(vertices, indices, textures);
}

vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type) {
    vector<Texture> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        filesystem::path filePath(directory);
        filePath = filePath.parent_path();
        filePath /= str.C_Str();
        filePath.make_preferred();
        if (textureLoaded.find(filePath.string()) != textureLoaded.end()) textures.push_back(textureLoaded[filePath.string()]);
        else
        {
            TextureType texType = TextureType::DIFFUSE;
            if (type == aiTextureType_DIFFUSE)
                texType = TextureType::DIFFUSE;
            else if (type == aiTextureType_SPECULAR)
                texType = TextureType::SPECULAR;
            else if (type == aiTextureType_HEIGHT)
                texType = TextureType::NORMAL;
            else if (type == aiTextureType_AMBIENT)
                texType = TextureType::HEIGHT;
            Texture texture(filePath.string(), true, GL_TEXTURE_WRAP_R, GL_LINEAR, texType);
            textureLoaded.insert({ filePath.string() , texture });
            textures.push_back(texture);
        }
    }
    return textures;
}

void Model::Draw(Shader& shader) {
    std::queue<ModelNode*> q;
    q.push(root);
    while(!q.empty())
    {
        ModelNode* curNode = q.front();
        q.pop();
        if (curNode == nullptr) break;
        for (auto mesh : curNode->meshes) mesh.Draw(shader);
        for (auto child : curNode->children) q.push(child);
    }
}

ModelNode* Model::getRootNode() const
{
    return root;
}
