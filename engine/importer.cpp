#include "importer.hpp"

#include <iostream>

std::vector<model> Importer::import(const std::string &path)
{
    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile("tic_tac_toe.obj", aiProcess_Triangulate | aiProcess_FlipUVs);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return { };
    }

    return process_node(scene->mRootNode, scene);
}

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

    // process indices
    std::vector<unsigned int> indices;
    for (unsigned int i = 0; i < pMesh->mNumFaces; i++)
    {
        const aiFace& face = pMesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
        {
            indices.push_back(face.mIndices[j]);
        }
    }

    model model;
    model.vertices = vertices;
    model.indices  = indices;

    return model;
}
