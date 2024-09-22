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
#define GET_SINGLE(classname)	classname::GetInstance()

#define GRAPHICS	GET_SINGLE(Graphics)
#define DEVICE		GET_SINGLE(Graphics).GetDevice()
#define DC			GET_SINGLE(Graphics).GetDeviceContext()

#define GAME		GET_SINGLE(Game)

#define MANAGER		GET_SINGLE(Manager)
#define TIME		MANAGER.GetManager<MANAGER_TYPE::Time>()
#define INPUT		MANAGER.GetManager<MANAGER_TYPE::Input>()
#define SCENE		MANAGER.GetManager<MANAGER_TYPE::Scene>()
#define RENDER		MANAGER.GetManager<MANAGER_TYPE::Render>()
#define GUI			MANAGER.GetManager<MANAGER_TYPE::Gui>()
#define SHADER		MANAGER.GetManager<MANAGER_TYPE::Shader>()
