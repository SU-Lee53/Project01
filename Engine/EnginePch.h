#pragma once

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
#include "Game.h"
#include "Utils.h"
#include "Manager.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "SceneManager.h"