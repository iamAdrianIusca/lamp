#include <glad/glad.h>

#include <vector>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "window.hpp"
#include "vertex_array.hpp"
#include "shader.hpp"
#include "buffer.hpp"
#include "keys.hpp"
#include "time.hpp"
#include "file.hpp"

std::vector<float> processNode(aiNode *pNode, const aiScene *pScene);
std::vector<float> processMesh(aiMesh *pMesh, const aiScene *pScene);

int main()
{
    const int width  = 800;
    const int height = 600;

    Window window;
    window.create("Game Engine", width, height);

    Shader shader(File::read_file("simple_vert.glsl").c_str(),
                  File::read_file("simple_frag.glsl").c_str());

    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile("cube.obj", aiProcess_Triangulate | aiProcess_FlipUVs);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return -1;
    }
    std::cout << "Loaded model: " << scene->mRootNode->mName.C_Str() << std::endl;

    // process node
    std::vector<float> vertices = processNode(scene->mRootNode, scene);

    VertexArray vao;
    vao.bind();

    // create vbo buffer for vertices
    Buffer vboBuffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW, vertices.size() * sizeof(float), vertices.data());

    // set vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // initialize delta time
    float lastFrame = 0.0f;

    glEnable(GL_DEPTH_TEST);

    // show the window
    while (!window.isClosed())
    {
        // calculate delta time
        auto currentFrame = Time::getTotalTime();
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // rotate glm matrix with delta time
        glm::mat4 rotate    = glm::rotate(glm::mat4(1.0f), Time::getTotalTime(), glm::vec3(1.0f, 1.0f, 1.0f));
        glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        glm::mat4 scale     = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 0.5f));

        // calculate perspective matrix with glm
        glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f));

        // close the window on escape key
        if (window.isKeyPressed(ESC_KEY))
        {
            window.close();
        }

        window.clear();

        shader.use();

        //glm::mat4 transform = scale * rotate * translate;
        glm::mat4 transform = translate * rotate * scale;

        shader.setMat4(0, glm::value_ptr(transform));
        shader.setMat4(1, glm::value_ptr(proj));
        shader.setMat4(2, glm::value_ptr(view));

        vao.bind();

        // draw triangle
        glDrawArrays(GL_TRIANGLES, 0, vertices.size());

        window.update();
    }

    window.destroy();

    return 0;
}

std::vector<float> processNode(aiNode *pNode, const aiScene *pScene)
{
    // process all meshes in node
    for (unsigned int i = 0; i < pNode->mNumMeshes; i++)
    {
        aiMesh* mesh = pScene->mMeshes[pNode->mMeshes[i]];
        return processMesh(mesh, pScene);
    }

    // process all children nodes
    for (unsigned int i = 0; i < pNode->mNumChildren; i++)
    {
        return processNode(pNode->mChildren[i], pScene);
    }

    return { };
}

std::vector<float> processMesh(aiMesh *pMesh, const aiScene *pScene)
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
