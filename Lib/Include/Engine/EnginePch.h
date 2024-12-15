#pragma once
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

// Types
#include "Types.h"
#include "Define.h"

// STL
#include <memory>
#include <iostream>
#include <array>
#include <vector>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <string>
#include <fstream>
#include <type_traits>
#include <concepts>
#include <any>
#include <variant>
#include <filesystem>
using namespace std;

// WIN
#include <windows.h>
#include <WinUser.h>
#include <assert.h>
#include <optional>

// DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

// ImGUI
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"

// Assimp
#include <Assimp/Importer.hpp>
#include <Assimp/scene.h>
#include <Assimp/postprocess.h>

// FreeType
// #include <FreeType/ft2build.h>
// #include FT_FREETYPE_H

// DX
#include <d3d11.h>
#include <d3dcompiler.h>
#include <d3d11shader.h>
#include <wrl.h>
#include <DirectXMath.h>
#include <DirectXTex/DirectXTex.h>
#include <DirectXTex/DirectXTex.inl>
using namespace DirectX;
using namespace Microsoft::WRL;

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

#ifdef _DEBUG
#pragma comment(lib, "DirectXTex/DirectXTex_debug.lib")
#pragma comment(lib, "Assimp/assimp-vc143-mtd.lib")
#else
#pragma comment(lib, "DirectXTex/DirectXTex.lib")
#pragma comment(lib, "Assimp/assimp-vc143-mt.lib")
#endif

#include "Game.h"
#include "Graphics.h"
#include "Manager.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "ShaderManager.h"
#include "RenderManager.h"
#include "GuiManager.h"
#include "ResourceManager.h"

// Engine
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "InputLayout.h"
#include "Geometry.h"
#include "InputData.h"
#include "ModelTypes.h"
#include "Shader_Base.h"
#include "ConstantBuffer.h"
#include "Texture.h"
#include "RasterizerState.h"
#include "SamplerState.h"
#include "BlendState.h"
#include "Pipeline.h"

#include "Transform.h"
#include "Camera.h"
#include "BaseCollider.h"
#include "SphereCollider.h"
#include "AABBCollider.h"
#include "OBBCollider.h"
#include "PlaneCollider.h"
#include "Script.h"
#include "Utils.h"