#pragma once
#include "Execute.h"

class SceneTest : public Execute
{
public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

private:
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

