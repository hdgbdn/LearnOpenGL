#pragma once
#include <assimp/Importer.hpp>
#include <assimp/scene.h>

#include "Mesh.h"
#include "Shader.h"
#include <string>
#include <vector>
#include <unordered_map>

namespace hdgbdn
{
	struct ModelNode
	{
		std::string name;
		vector<Mesh> meshes;
		vector<ModelNode*> children;
	};
	
	class Model {
	public:
		Model(const std::string&);
		~Model();
		void Draw(Shader&);
		ModelNode* getRootNode() const;
	private:
		ModelNode* root;
		string name;
		string directory;
		std::unordered_map<std::string, Texture> textureLoaded;
		void loadModel(const std::string&);
		ModelNode* processNode(aiNode* node, const aiScene* scene);
		Mesh processMesh(aiMesh* mesh, const aiScene* scene);
		vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type);
		
		static void DeleteModelTree(ModelNode*);
	};
}
