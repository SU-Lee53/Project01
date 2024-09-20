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
#define TIME		MANAGER.GetManager<MANAGER_TYPE::Time>()
#define INPUT		MANAGER.GetManager<MANAGER_TYPE::Input>()
#define SCENE		MANAGER.GetManager<MANAGER_TYPE::Scene>()
#define RENDER		MANAGER.GetManager<MANAGER_TYPE::Render>()
#define GUI			MANAGER.GetManager<MANAGER_TYPE::Gui>()



#define IDENTITY	glm::mat4(1.0f)

#define AXIS_X		glm::vec3{1.0f, 0.0f, 0.0f}
#define AXIS_Y		glm::vec3{0.0f, 1.0f, 0.0f}
#define AXIS_Z		glm::vec3{0.0f, 0.0f, 1.0f}