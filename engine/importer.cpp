#include "importer.hpp"

#include <iostream>

std::vector<model> Importer::import(const std::string& path)
{
    Assimp::Importer importer;

    const auto* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return { };
    }

    return process_node(scene->mRootNode, scene);
}

std::vector<model> Importer::process_node(aiNode* pNode, const aiScene *pScene)
{
    std::vector<model> models;
    models.reserve(pNode->mNumMeshes);

    // process all meshes in node
    for (unsigned int i = 0; i < pNode->mNumMeshes; i++)
    {
        const auto* mesh = pScene->mMeshes[pNode->mMeshes[i]];

        models.push_back(process_mesh(mesh));
    }

    // process all children nodes
    for (unsigned int i = 0; i < pNode->mNumChildren; i++)
    {
        auto children = process_node(pNode->mChildren[i], pScene);

        models.insert(models.end(), children.begin(),
                                    children.end());
    }

    return models;
}

model Importer::process_mesh(const aiMesh* pMesh)
{
    constexpr int32_t triangle_vertices = 3;

    std::vector<vertex> vertices;
    vertices.reserve(pMesh->mNumVertices);

    for (unsigned int i = 0; i < pMesh->mNumVertices; i++)
    {
        const aiVector3D& pos = pMesh->mVertices[i];

        vertices.push_back({ pos.x, pos.y, pos.z });
    }

    std::vector<unsigned int> indices;
    indices.reserve(pMesh->mNumFaces * triangle_vertices);

    for (unsigned int i = 0; i < pMesh->mNumFaces; i++)
    {
        const aiFace& face = pMesh->mFaces[i];
        for (unsigned int j = 0; j < triangle_vertices; j++)
        {
            indices.push_back(face.mIndices[j]);
        }
    }

    model model;
    model.vertices = vertices;
    model.indices  = indices;
    model.submeshes.push_back({ 0, static_cast<int>(indices.size()) });

    return model;
}