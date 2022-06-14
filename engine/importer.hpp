#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vector>

class Importer
{
public:
    static std::vector<float> process_node(aiNode *pNode, const aiScene *pScene);
    static std::vector<float> process_mesh(aiMesh *pMesh, const aiScene *pScene);
};