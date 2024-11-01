#pragma once
#include <concepts>
#include "Manager.h"
#include "Collider.h"

template <typename C>
concept IsColliderType = requires(C c)
{
	std::derived_from<C, Collider>;
};

template <typename C>
concept ColliderType = IsColliderType<C>;


template <typename C>
concept IsManagerType = requires(C c)
{
	std::derived_from<C, Manager_Base>;
};

template <typename C>
concept ManagerType = IsManagerType<C>;


template <typename C>
concept IsShaderType = requires(C c)
{
	std::same_as<C, ID3D11VertexShader> or
		std::same_as<C, ID3D11HullShader> or
		std::same_as<C, ID3D11DomainShader> or
		std::same_as<C, ID3D11GeometryShader> or
		std::same_as<C, ID3D11PixelShader> or
		std::same_as<C, ID3D11ComputeShader>;
};

template <typename C>
concept ShaderType = IsShaderType<C>;



