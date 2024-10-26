#include "pch.h"
#include "ModelLoader.h"
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

void ModelLoader::Init()
{
	_converter = make_shared<Converter>();

	_obj = make_shared<GameObject>();
	{
		_obj->AddComponent<Transform>();
		_obj->AddComponent<MeshRenderer>();
		_obj->Init();

		_converter->LoadAssetFile(L"../Models/pool/pool_1.fbx", L"../Models/pool/src/");
		_converter->ExportAssetFile(L"pool");

		auto model = make_shared<Model>();
		model = _converter->MakeModel();
		_obj->GetComponent<MeshRenderer>()->SetModel(model);

		_mouseScript = make_shared<ModelScript>();
		_obj->AddScript(_mouseScript);
	}

	_cam = make_shared<GameObject>();
	{
		_cam->AddComponent<Transform>();
		_cam->AddComponent<Camera>();
		_cam->Init();

		_cam->GetComponent<Transform>()->SetPosition(Vec3{ 0.0f, 0.0f, -5.0f });

		_mouseScript = make_shared<MouseScript>();
		_cam->AddScript(_mouseScript);
	}

	_light = make_shared<GameObject>();
	{
		_light->AddComponent<Transform>();
		_light->AddComponent<GlobalLight>();
		_light->Init();

		GlobalLightData data;
		{
			data.ambient = Vec4(0.5f);
			data.diffuse = Vec4(1.0f);
			data.specular = Vec4(1.0f, 1.0f, 1.0f, 1.0f);
			data.direction = Vec3(0.0f, -1.0f, 0.0f);
		}

		_light->GetComponent<GlobalLight>()->SetData(data);

	}

}

void ModelLoader::Update()
{
	if (ImGui::Begin("Test on TestExe"))
	{
		ImGui::Text("MousePos.x : %li", INPUT->GetMousePos().x);
		ImGui::Text("MousePos.y : %li", INPUT->GetMousePos().y);

		auto pos = _cam->GetComponent<Transform>()->GetPosition();
		ImGui::Text("CameraPos.x : %f", pos.x);
		ImGui::Text("CameraPos.y : %f", pos.y);
		ImGui::Text("CameraPos.z : %f", pos.z);

	}
	ImGui::End();

	if (ImGui::Begin("ModelLoader"))
	{
		auto callBacks = [](ImGuiInputTextCallbackData* data) -> int
			{
				if (data->EventFlag == ImGuiInputTextFlags_CallbackCompletion)
				{
					data->InsertChars(data->CursorPos, "/");
				}
				else if (data->EventFlag == ImGuiInputTextFlags_CallbackResize)
				{
					string* str = static_cast<string*>(data->UserData);
					IM_ASSERT(str->data() == data->Buf);
					str->resize(data->BufSize);
					data->Buf = str->data();
				}
				return 0;
			};

		ImGuiInputTextFlags flags = ImGuiInputTextFlags_CallbackCompletion | ImGuiInputTextFlags_CallbackResize;

		ImGui::InputText(".fbx path", modelTemp.data(), (size_t)modelTemp.size(), flags, callBacks, (void*)&modelTemp);
		ImGui::InputText("texture path", textureTemp.data(), (size_t)textureTemp.size(), flags, callBacks, (void*)&textureTemp);

		if (ImGui::Button("Load"))
		{
			ImGui::Text("Loading");

			_entered = true;
			QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&_timeStamp));

			_modelPath = Utils::ToWString(modelTemp);
			_texturePath = Utils::ToWString(textureTemp);

			auto modelP = filesystem::path(_modelPath);
			auto textureP = filesystem::path(_texturePath);

			if (!filesystem::exists(modelP)) assert(false);
			if (!filesystem::exists(textureP)) assert(false);

			_converter->Reset();
			_converter->LoadAssetFile(modelP, textureP);
			auto model = _converter->MakeModel();
			_obj->GetComponent<MeshRenderer>()->SetModel(model);

		}

		if (_entered == true)
		{
			ImGui::Text("Load Complete");
			uint64 _currTime;
			QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&_currTime));
			if (_currTime - _timeStamp > 15000000)
				_entered = false;
		}

		ImGui::Text("_modelPath : %s", Utils::ToString(_converter->GetCurrentModelPath()).c_str());
		ImGui::Text("_texturePath : %s", Utils::ToString(_converter->GetCurrentMaterialPath()).c_str());
	}
	ImGui::End();


	_converter->ShowMaterials();

	_obj->Update();
	_cam->Update();
	_light->Update();
}

void ModelLoader::Render()
{
	RENDER->Render();
}
