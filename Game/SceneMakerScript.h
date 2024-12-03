#pragma once
#include <Script.h>


/*
	- What we need
		1. Make Object and add to scene
		2. Modify Object in scene
			- AddComponent
			- AddCollider
			- Modify Component(Transform)
		3. Save / Load Scene
			- Save What?
				- Scene _name
				- Objs
				- Cams
				- Scripts?
*/

class SceneMakerScript : public Script<Scene>
{
public:
	virtual void Init() override;
	virtual void Update() override;

public:
	void SaveScene();
	void LoadScene();

private:
	// Obj Loader() and variables
	void ObjLoader();

private:
	void SceneController();
	void ControlGlobalLight(shared_ptr<GameObject> light);
	char _name[128];
	Vec3 cam_pos;
	Vec3 cam_dir;

	int32 sc_itemSelected = 0;
	bool sc_itemHighlighted = 0;
	int32 sc_itemHighlightedIdx = 0;
	const char* sc_previewName;
	int32 sc_prevComboListSize = 0;
	
	int32 sc_cam_itemSelected = 0;
	bool sc_cam_itemHighlighted = 0;
	int32 sc_cam_itemHighlightedIdx = 0;
	const char* sc_cam_previewName;
	int32 sc_cam_prevComboListSize = 0;

	GlobalLightData sc_lightData;

private:
	void ComponentModifier();
	void TransformModifier(shared_ptr<GameObject> target);
	void MeshRendererModifier(shared_ptr<GameObject> target);
	
	float _dragSpeed = 1.f; 
	bool _scaleType = false;

	int32 mm_itemSelected = 0;
	bool mm_itemHighlighted = 0;
	int32 mm_itemHighlightedIdx = 0;



private:
	void UpdateComboList();

private:
	// LoadedObj Combo Variables
	int32 lo_itemSelected = 0;
	bool lo_itemHighlighted = 0;
	int32 lo_itemHighlightedIdx = 0;
	const char* lo_previewName;
	int32 lo_prevComboListSize = 0;

private:
	vector<pair<string, shared_ptr<GameObject>>> LoadedObjs;

	vector<wstring> LoadTargets =
	{
		//L"pool_cue.mesh",
		//L"floor.mesh",
		//L"pool_ball_1.mesh",
		//L"pool_ball_2.mesh",
		//L"pool_ball_3.mesh",
		//L"pool_ball_4.mesh",
		//L"pool_ball_5.mesh",
		//L"pool_ball_6.mesh",
		//L"pool_ball_7.mesh",
		//L"pool_ball_8.mesh",
		//L"pool_ball_9.mesh",
		//L"pool_ball_10.mesh",
		//L"pool_ball_11.mesh",
		//L"pool_ball_12.mesh",
		//L"pool_ball_13.mesh",
		//L"pool_ball_14.mesh",
		//L"pool_ball_15.mesh",
		//L"pool_objectball.mesh",
		//L"pool_table.mesh"
	};
};

