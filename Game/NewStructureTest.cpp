#include "pch.h"
#include "NewStructureTest.h"
#include "Converter.h"
#include "GameObject.h"
#include "Model.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "Camera.h"
#include "MouseScript.h"
#include "ModelScript.h"
#include "GlobalLight.h"
#include <filesystem>

void NewStructureTest::Init()
{
}

void NewStructureTest::Update()
{
	if (ImGui::Begin("Shaders"))
	{
		auto vss = RESOURCE->GetVertexShaderSet();
		auto pss = RESOURCE->GetPixelShaderSet();

		if (ImGui::TreeNode("VertexShaders"))
		{
			for (const auto& vs : vss)
			{
				ImGui::BulletText("name : %s", vs->GetName().c_str());
			}

			ImGui::TreePop();
		}

		if (ImGui::TreeNode("PixelShaders"))
		{
			for (const auto& ps : pss)
			{
				ImGui::BulletText("name : %s", ps->GetName().c_str());
			}

			ImGui::TreePop();
		}
	}
	ImGui::End();
}

void NewStructureTest::Render()
{
	RENDER->Render();
}
