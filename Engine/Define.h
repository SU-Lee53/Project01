#pragma once

#define DECLARE_SINGLE(classname)			\
private:									\
	classname() { }							\
public:										\
	static classname& GetInstance()			\
	{										\
		static classname s_instance;		\
		return s_instance;					\
	}


#define HR_ASSERT(p)	assert(SUCCEEDED(p))
#define AI_ASSERT(p)	assert(p != AI_SUCCESS)
#define GET_SINGLE(classname)	classname::GetInstance()

#define GRAPHICS		GET_SINGLE(Graphics)
#define DEVICE			GET_SINGLE(Graphics).GetDevice()
#define DC				GET_SINGLE(Graphics).GetDeviceContext()

#define GAME			GET_SINGLE(Game)

#define MANAGER			GET_SINGLE(Manager)
#define TIME			MANAGER.GetManager<TimeManager>()
#define INPUT			MANAGER.GetManager<InputManager>()
#define SCENE			MANAGER.GetManager<SceneManager>()
#define RENDER			MANAGER.GetManager<RenderManager>()
#define GUI				MANAGER.GetManager<GuiManager>()
#define SHADER			MANAGER.GetManager<ShaderManager>()
#define RESOURCE		MANAGER.GetManager<ResourceManager>()


#define DELTA_TIME		TIME->GetDeltaTime();