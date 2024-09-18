#pragma once
#define WIN32_LEAN_AND_MEAN

// WIN
#include <windows.h>

// Types
#include "Types.h"
#include "Define.h"

// STL
#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <memory>
#include <vector>
#include <unordered_map>
#include <type_traits>
#include <array>
#include <variant>
#include <filesystem>
#include <fstream>

using namespace std;

// OPENGL
#pragma comment (lib, "freeglut/freeglut.lib")
#pragma comment (lib, "glew/glew32.lib")

#include <gl/glew.h>
#include <freeglut/freeglut.h>
#include <freeglut/freeglut_ext.h>
// glm types are included in Types.h


// PreCompile
#include "Manager.h"
#include "Component.h"

#include "Utils.h"
#include "Shader.h"
#include "VAO.h"
#include "GameObject.h"
#include "Game.h"