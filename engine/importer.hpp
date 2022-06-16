#pragma once

#include "vertex.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vector>

struct model
{
    std::vector<vertex>       vertices;
    std::vector<unsigned int> indices;
};

class Importer
{
public:
    static std::vector<model> import(const std::string& path);

private:
    static std::vector<model> process_node(aiNode *pNode, const aiScene *pScene);
    static model process_mesh(aiMesh *pMesh, const aiScene *pScene);
};