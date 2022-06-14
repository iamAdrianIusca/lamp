#include "importer.hpp"

#include <iostream>

std::vector<model> Importer::process_node(aiNode *pNode, const aiScene *pScene)
{
    std::vector<model> models;

    // process all meshes in node
    for (unsigned int i = 0; i < pNode->mNumMeshes; i++)
    {
        aiMesh* mesh = pScene->mMeshes[pNode->mMeshes[i]];
        models.push_back(process_mesh(mesh, pScene));
    }

    // process all children nodes
    for (unsigned int i = 0; i < pNode->mNumChildren; i++)
    {
        std::vector<model> child_models = process_node(pNode->mChildren[i], pScene);
        models.insert(models.end(), child_models.begin(), child_models.end());
    }

    std::cout << "Models count: " << models.size() << std::endl;
    return models;
}

model Importer::process_mesh(aiMesh *pMesh, const aiScene *pScene)
{
    // process vertices
    std::vector<vertex> vertices;
    for (unsigned int i = 0; i < pMesh->mNumVertices; i++)
    {
        const aiVector3D& pos = pMesh->mVertices[i];

        vertices.push_back({ pos.x, pos.y, pos.z });
    }

    model model;
    model.vertices = vertices;

    return model;
}