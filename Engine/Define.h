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


#define GET_SINGLE(classname)	classname::GetInstance()

#define MANAGER		GET_SINGLE(Manager)
#define TIME		MANAGER.GetManager<ManagerType::Time>()
#define INPUT		MANAGER.GetManager<ManagerType::Input>()
#define SCENE		MANAGER.GetManager<ManagerType::Scene>()


#define IDENTITY	glm::mat4(1.0f);