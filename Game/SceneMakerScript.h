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
				- Scene name
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

	char name[128];


private:
	void UpdateComboList();

private:
	void ControlComponent();




private:

private:
	// LoadedObj Combo Variables
	int32 itemSelected = 0;
	const char* previewName;
	int32 prevComboListSize = 0;

private:
	vector<pair<string, shared_ptr<GameObject>>> LoadedObjs;

	vector<wstring> LoadTargets =
	{
		L"pool_cue.mesh",
		L"floor.mesh",
		L"pool_ball_1.mesh",
		L"pool_ball_2.mesh",
		L"pool_ball_3.mesh",
		L"pool_ball_4.mesh",
		L"pool_ball_5.mesh",
		L"pool_ball_6.mesh",
		L"pool_ball_7.mesh",
		L"pool_ball_8.mesh",
		L"pool_ball_9.mesh",
		L"pool_ball_10.mesh",
		L"pool_ball_11.mesh",
		L"pool_ball_12.mesh",
		L"pool_ball_13.mesh",
		L"pool_ball_14.mesh",
		L"pool_ball_15.mesh",
		L"pool_objectball.mesh",
		L"pool_table.mesh"
	};
};

