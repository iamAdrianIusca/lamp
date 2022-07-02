#pragma once

#ifdef LAMP_WIN32
#include <glad/glad.h>
#elif  LAMP_WEB
#include <GL/glew.h>
#include <emscripten.h>
#endif

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <btBulletCollisionCommon.h>

#include <cstddef>
#include <cassert>
#include <cstdint>

#include <functional>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>