#pragma once

#include "model.hpp"
#include "vertex.hpp"
#include "mesh.hpp"

class Importer
{
public:
    static std::vector<model> import(const std::string& path);

private:
    static std::vector<model> process_node(aiNode *pNode, const aiScene *pScene);
    static model              process_mesh(const aiMesh *pMesh);
};