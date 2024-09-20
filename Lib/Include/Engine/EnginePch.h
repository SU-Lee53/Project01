#pragma once
#define WIN32_LEAN_AND_MEAN

// Types
#include "Types.h"
#include "Define.h"

// STL
#include <memory>
#include <iostream>
#include <array>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <fstream>
#include <type_traits>
using namespace std;

// WIN
#include <windows.h>
#include <assert.h>
#include <optional>

// DX
#include <d3d11.h>
#include <d3dcompiler.h>
#include <d3d11shader.h>
#include <d3d11.h>
#include <wrl.h>
#include <DirectXMath.h>
#include <DirectXTex/DirectXTex.h>
#include <DirectXTex/DirectXTex.inl>
using namespace DirectX;
using namespace Microsoft::WRL;

#ifdef _DEBUG
#pragma comment(lib, "DirectXTex/DirectXTex_debug.lib")
#else
#pragma comment(lib, "DirectXTex/DirectXTex.lib")
#endif


//// OPENGL
//#pragma comment (lib, "freeglut/freeglut.lib")
//#pragma comment (lib, "glew/glew32.lib")
//
//#include <gl/glew.h>
//#include <freeglut/freeglut.h>
//#include <freeglut/freeglut_ext.h>
//// glm types are included in Types.h

// PreCompile
#include "Game.h"
#include "Manager.h"
#include "Component.h"

//#include "Utils.h"
//#include "Shader.h"
//#include "GameObject.h"
