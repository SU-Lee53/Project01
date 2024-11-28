#include "EnginePch.h"
#include "Model.h"
#include "Material.h"
#include <filesystem>

Model::Model()
{
}

Model::~Model()
{
}

void Model::SetBone(vector<shared_ptr<ModelBone>> bone)
{
	_bones = bone;
	_root = bone[0];
}


/////////////// Load Model From .mesh File ///////////////
#pragma region Loader

void Model::LoadFromFiles(const wstring& fileName)
{
	wstring path = L"../Resources/Models/" + fileName;

	auto filePath = filesystem::path(path);
	assert(filesystem::exists(path));

	ifstream is(filePath);
	assert(is.is_open(), "failed to open " + Utils::ToString(path));
	assert(!is.fail(), "istream failed");

	shared_ptr<ModelMesh> mesh = make_shared<ModelMesh>();
	mesh->geometry = make_shared<Geometry<VertexType>>();

	shared_ptr<Material> material = make_shared<Material>();

	LoadNames(is);

	LoadVertices(is, mesh);
	LoadIndices(is, mesh);
	mesh->MakeBuffers();
	mesh->materialIndex = 0;

	LoadBones(is, mesh);
	_meshes.push_back(mesh);

	LoadMaterials(is);
	_materials.push_back(material);

	is.close();
}

		//////////////////////////////////
		// 3 steps						//
		// 1. check ### begin			//
		// 2. read until ### end shows	//
		// 3. modify					//
		//////////////////////////////////

void Model::LoadNames(ifstream& is)
{
	assert(is.is_open(), "failed to open " + Utils::ToString(path));
	assert(!is.fail(), "istream failed");

	string read;

	while (true)
	{
		getline(is, read);
		if (read.contains("names begin")) break;
	}

	while (true)
	{
		getline(is, read);
		if (read.contains("names end")) break;
		
		// we don't have names yet so skip this part
	}

}

void Model::LoadVertices(ifstream& is, OUT shared_ptr<ModelMesh> mesh)
{
	assert(is.is_open(), "failed to open " + Utils::ToString(path));
	assert(!is.fail(), "istream failed");

	string read;

	while (true)
	{
		getline(is, read);
		if (read.contains("vertices begin")) break;
	}

	vector<VertexType> vertices;

	while (true)
	{
		getline(is, read);
		if (read.contains("vertices end")) break;

		VertexType vtx;
		float vec[3];

		// position
		size_t pos = 0;
		size_t prev = 0;

		for (int i = 0; i < 3; i++)
		{
			pos = read.find(' ', prev);
			auto sub = read.substr(prev, pos - prev);
			{
				vec[i] = stof(sub);
			}
			prev = pos + 1;
		}
		vtx.position = Vec3(vec);

		// uv
		getline(is, read);
		for (int i = 0; i < 2; i++)
		{
			pos = read.find(' ', prev);
			auto sub = read.substr(prev, pos - prev);
			{
				vec[i] = stof(sub);
			}
			prev = pos + 1;
		}
		vtx.uv = Vec2(vec);

		// normal
		getline(is, read);
		for (int i = 0; i < 3; i++)
		{
			pos = read.find(' ', prev);
			auto sub = read.substr(prev, pos - prev);
			{
				// substr -> pos
				vec[i] = stof(sub);
			}
			prev = pos + 1;
		}
		vtx.normal = Vec3(vec);

		// tangent
		getline(is, read);
		for (int i = 0; i < 3; i++)
		{
			pos = read.find(' ', prev);
			auto sub = read.substr(prev, pos - prev);
			{
				// substr -> pos
				vec[i] = stof(sub);
			}
			prev = pos + 1;
		}
		vtx.tangent = Vec3(vec);
		
		// Add
		vertices.push_back(vtx);
	}

	mesh->geometry->SetVertices(vertices);

}

void Model::LoadIndices(ifstream& is, OUT shared_ptr<ModelMesh> mesh)
{
	assert(is.is_open(), "failed to open " + Utils::ToString(path));
	assert(!is.fail(), "istream failed");

	string read;

	while (true)
	{
		getline(is, read);
		if (read.contains("indices begin")) break;
	}

	vector<uint32> indices;

	while (true)
	{
		getline(is, read);
		if (read.contains("indices end")) break;

		uint32 idx = stoi(read);
		indices.push_back(idx);
	}

	mesh->geometry->SetIndices(indices);

}

void Model::LoadBones(ifstream& is, OUT shared_ptr<ModelMesh> mesh)
{
	assert(is.is_open(), "failed to open " + Utils::ToString(path));
	assert(!is.fail(), "istream failed");

	string read;

	while (true)
	{
		getline(is, read);
		if (read.contains("bones begin")) break;
	}

	// boneIndex
	getline(is, read);
	mesh->boneIndex = stoi(read);

	while(true)
	{
		getline(is, read);
		if (read.contains("bones end")) break;
		
		shared_ptr<ModelBone> bone = make_shared<ModelBone>();

		// name
		bone->name = Utils::ToWString(read);

		// index
		getline(is, read);
		bone->index = stoi(read);

		// parent
		getline(is, read);
		bone->parentIndex = stoi(read);

		// transform
		size_t pos = 0;
		size_t prev = 0;
		float matrix[4][4]; 

		for (uint32 i = 0; i < 4; i++)
		{
			getline(is, read);
			for (uint32 j = 0; j < 4; j++)
			{
				pos = read.find(' ', prev);
				auto sub = read.substr(prev, pos - prev);
				{
					// substr -> pos'
					matrix[i][j] = stof(sub);
				}
				prev = pos + 1;
			}
		}
		bone->transform = Matrix((float*)matrix);

		_bones.push_back(bone);
	}

	_root = _bones.front();

}

void Model::LoadMaterials(ifstream& is)
{
	assert(is.is_open(), "failed to open " + Utils::ToString(path));
	assert(!is.fail(), "istream failed");

	string read;

	while (true)
	{
		getline(is, read);
		if (read.contains("materials begin")) break;
	}

	while (true)
	{
		shared_ptr<Material> material = make_shared<Material>();

		getline(is, read);
		if (read.contains("materials end")) break;

		// material name
		wstring name = Utils::ToWString(read);
		material->SetName(name);

		float color[4];
		MaterialData data;

		size_t pos = 0;
		size_t prev = 0;

		// Material Data(colors)
		{
			// diffuse
			getline(is, read);
			for (int i = 0; i < 4; i++)
			{
				pos = read.find(' ', prev);
				auto sub = read.substr(prev, pos - prev);
				{
					color[i] = stof(sub);
				}
				prev = pos + 1;
			}
			data.diffuse = Color(color);

			// specular
			getline(is, read);
			for (int i = 0; i < 4; i++)
			{
				pos = read.find(' ', prev);
				auto sub = read.substr(prev, pos - prev);
				{
					color[i] = stof(sub);
				}
				prev = pos + 1;
			}
			data.specular = Color(color);

			// ambient
			getline(is, read);
			for (int i = 0; i < 4; i++)
			{
				pos = read.find(' ', prev);
				auto sub = read.substr(prev, pos - prev);
				{
					color[i] = stof(sub);
				}
				prev = pos + 1;
			}
			data.ambient = Color(color);

			// emissive
			getline(is, read);
			for (int i = 0; i < 4; i++)
			{
				pos = read.find(' ', prev);
				auto sub = read.substr(prev, pos - prev);
				{
					color[i] = stof(sub);
				}
				prev = pos + 1;
			}
			data.ambient = Color(color);
		}

		material->SetMaterialData(data);

		// textures
		{
			wstring path = L"../Resources/Materials/Texture/" + material->GetName() + L'/';
			uint8 flag = 0;

			for (uint32 i = 0; i < 3; i++)
			{
				shared_ptr<Texture> tex = make_shared<Texture>();

				getline(is, read);
				if (read != "None")
				{
					string fileName = filesystem::path(read).filename().string();
					wstring filePath = path + Utils::ToWString(fileName);
					tex->Create(filePath);
				}
				else
				{
					tex->CreateErrorTexture();
				}

				// Set flag
				switch (i)
				{
				case 0:
					material->SetDiffuseMap(tex);
					if (tex->IsErrorTexture() == false)
					{
						flag |= HAS_DIFFUSE;
					}
					break;

				case 1:
					material->SetSpecularMap(tex);
					if (tex->IsErrorTexture() == false)
					{
						flag |= HAS_SPECULAR;
					}
					break;

				case 2:
					material->SetNormalMap(tex);
					if (tex->IsErrorTexture() == false)
					{
						flag |= HAS_NORMAL;
					}
					break;

				default:
					assert(false);
				}

			}

			material->SetMaterialAttributes((MaterialFlag)flag);
		}

		// TODO : Set Shader by Attribute(flag)
		material->SetVertexShader(SHADER->GetVertexShader("Vertex.hlsl"));
		if (Material::CheckAttributes(material->_attributes, HAS_NORMAL))
		{
			material->SetPixelShader(SHADER->GetPixelShader("PixelWithNormal.hlsl"));
		}
		else
		{
			material->SetPixelShader(SHADER->GetPixelShader("PixelWithoutNormal.hlsl"));
		}

		_materials.push_back(material);
	}

}

#pragma endregion Loader


void Model::ShowModelHierarchy()
{
	for (const auto& model : _meshes)
	{
		if (ImGui::TreeNode("Show"))
		{
			ImGui::BulletText(
				"name : %s\n"
				"materialName : %s\n"
				"materialIndex : %d\n"
				"boneIndex : %d",
				Utils::ToString(model->name).c_str(),
				Utils::ToString(model->materialName).c_str(),
				model->materialIndex,
				model->boneIndex
			);

			if (ImGui::TreeNode("Material"))
			{
				auto m = _materials[model->materialIndex];
				if (ImGui::TreeNode("_materialData"))
				{
					if (ImGui::TreeNode("ambient"))
					{
						ImGui::BulletText(
							"ambient : R. %.3f G. %.3f B. %.3f A. %.3f\n",
							m->GetMaterialData().ambient.x, m->GetMaterialData().ambient.y, m->GetMaterialData().ambient.z, m->GetMaterialData().ambient.w
						);
						ImGui::TreePop();
					}

					if (ImGui::TreeNode("diffuse"))
					{
						ImGui::BulletText(
							"diffuse : R. %.3f G. %.3f B. %.3f A. %.3f\n",
							m->GetMaterialData().diffuse.x, m->GetMaterialData().diffuse.y, m->GetMaterialData().diffuse.z, m->GetMaterialData().diffuse.w
						);
						ImGui::TreePop();
					}

					if (ImGui::TreeNode("specular"))
					{
						ImGui::BulletText(
							"specular : R. %.3f G. %.3f B. %.3f A. %.3f\n",
							m->GetMaterialData().specular.x, m->GetMaterialData().specular.y, m->GetMaterialData().specular.z, m->GetMaterialData().specular.w
						);
						ImGui::TreePop();
					}

					if (ImGui::TreeNode("emissive"))
					{
						ImGui::BulletText(
							"emissive : R. %.3f G. %.3f B. %.3f A. %.3f\n",
							m->GetMaterialData().emissive.x, m->GetMaterialData().emissive.y, m->GetMaterialData().emissive.z, m->GetMaterialData().emissive.w
						);
						ImGui::TreePop();
					}

					ImGui::TreePop();
				}

				if (ImGui::TreeNode("_diffuseMap"))
				{
					ImGui::BulletText(
						"(from Resource_Base) _name : %s\n"
						"(from Resource_Base) _path : %s\n"
						"(from Resource_Base) _id : %d\n"
						"_size : (%.3f, %.3f)\n"
						"_isErrorTexture : %s\n",
						Utils::ToString(m->GetDiffuseMap()->GetName()).c_str(),
						Utils::ToString(m->GetDiffuseMap()->GetPath()).c_str(),
						m->GetDiffuseMap()->GetID(),
						m->GetDiffuseMap()->GetSize().x, m->GetDiffuseMap()->GetSize().y,
						m->GetDiffuseMap()->IsErrorTexture() ? "True" : "False"
					);

					ImGui::TreePop();
				}

				if (ImGui::TreeNode("_normalMap"))
				{
					ImGui::BulletText(
						"(from Resource_Base) _name : %s\n"
						"(from Resource_Base) _path : %s\n"
						"(from Resource_Base) _id : %d\n"
						"_size : (%.3f, %.3f)\n"
						"_isErrorTexture : %s\n",
						Utils::ToString(m->GetNormalMap()->GetName()).c_str(),
						Utils::ToString(m->GetNormalMap()->GetPath()).c_str(),
						m->GetNormalMap()->GetID(),
						m->GetNormalMap()->GetSize().x, m->GetNormalMap()->GetSize().y,
						m->GetNormalMap()->IsErrorTexture() ? "True" : "False"
					);

					ImGui::TreePop();
				}

				if (ImGui::TreeNode("_specularMap"))
				{
					ImGui::BulletText(
						"(from Resource_Base) _name : %s\n"
						"(from Resource_Base) _path : %s\n"
						"(from Resource_Base) _id : %d\n"
						"_size : (%.3f, %.3f)\n"
						"_isErrorTexture : %s\n",
						Utils::ToString(m->GetSpecularMap()->GetName()).c_str(),
						Utils::ToString(m->GetSpecularMap()->GetPath()).c_str(),
						m->GetSpecularMap()->GetID(),
						m->GetSpecularMap()->GetSize().x, m->GetSpecularMap()->GetSize().y,
						m->GetSpecularMap()->IsErrorTexture() ? "True" : "False"
					);

					ImGui::TreePop();
				}

				ImGui::TreePop();
			}

			if (ImGui::TreeNode("Bones"))
			{
				if (ImGui::BeginTable("Bones", 4, ImGuiTableFlags_BordersV | ImGuiTableFlags_BordersOuterH | ImGuiTableFlags_Resizable | ImGuiTableFlags_RowBg | ImGuiTableFlags_NoBordersInBody))
				{
					ImGui::TableSetupColumn("name");
					ImGui::TableSetupColumn("index");
					ImGui::TableSetupColumn("parentIndex");
					ImGui::TableSetupColumn("transform");
					ImGui::TableHeadersRow();

					ShowBoneNode(_bones[model->boneIndex], _bones);

					ImGui::EndTable();
				}
				ImGui::TreePop();
			}

			ImGui::TreePop();
		}
	}
}

void Model::ShowBoneNode(shared_ptr<ModelBone> node, vector<shared_ptr<ModelBone>> all_nodes)
{
	ImGui::TableNextRow();
	ImGui::TableNextColumn();

	if (node->parentIndex != -1)
	{
		bool open = ImGui::TreeNodeEx(Utils::ToString(node->name).c_str(), ImGuiTreeNodeFlags_SpanAllColumns);
		ImGui::TableNextColumn();
		ImGui::Text("%d", node->index);
		ImGui::TableNextColumn();
		ImGui::Text("%d", node->parentIndex);
		ImGui::TableNextColumn();
		Utils::ShowMatrix(node->transform);
		if (open)
		{
			ShowBoneNode(all_nodes[node->parentIndex], all_nodes);
			ImGui::TreePop();
		}
	}
	else if (node->parentIndex == -1 or node->parentIndex > all_nodes.size())
	{
		ImGui::TreeNodeEx(Utils::ToString(node->name).c_str(), ImGuiTreeNodeFlags_SpanAllColumns | ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_Bullet | ImGuiTreeNodeFlags_NoTreePushOnOpen);
		ImGui::TableNextColumn();
		ImGui::Text("%d", node->index);
		ImGui::TableNextColumn();
		ImGui::Text("%d", node->parentIndex);
		ImGui::TableNextColumn();
		Utils::ShowMatrix(node->transform);
	}
}
