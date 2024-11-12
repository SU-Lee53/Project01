#pragma once
#include <Script.h>
class SceneModelController : public Script<Scene>
{
public:
	virtual void Init() override;
	virtual void Update() override;

private:
	void UpdateComboList();
private:
	vector<pair<string, shared_ptr<GameObject>>> _items;
	
private:
	// Imgui Values
	int32 itemSelected = 0;
	const char* previewName;
	float _dragSpeed = 0.1f;
	bool _scaleType = true;

	int32 prevComboListSize = 0;
};

