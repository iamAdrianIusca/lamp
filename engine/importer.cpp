#include "importer.hpp"

std::vector<float> Importer::process_node(aiNode *pNode, const aiScene *pScene)
{
    // process all meshes in node
    for (unsigned int i = 0; i < pNode->mNumMeshes; i++)
    {
        aiMesh* mesh = pScene->mMeshes[pNode->mMeshes[i]];
        return process_mesh(mesh, pScene);
    }

    // process all children nodes
    for (unsigned int i = 0; i < pNode->mNumChildren; i++)
    {
        return process_node(pNode->mChildren[i], pScene);
    }

    return { };
}

std::vector<float> Importer::process_mesh(aiMesh *pMesh, const aiScene *pScene)
{
    // process vertices
    std::vector<float> vertices;
    for (unsigned int i = 0; i < pMesh->mNumVertices; i++)
    {
        const aiVector3D& pos = pMesh->mVertices[i];

        vertices.push_back(pos.x);
        vertices.push_back(pos.y);
        vertices.push_back(pos.z);
    }

    return vertices;
}