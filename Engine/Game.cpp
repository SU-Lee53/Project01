#include "EnginePch.h"
#include "Game.h"
#include "Shader.h"

void Game::Init(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(_desc.windowPos.x, _desc.windowPos.y);
	glutInitWindowSize(_desc.width, _desc.height);
	glutCreateWindow(_desc.windowName.c_str());

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Unable to init GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
	{
		std::cout << "GLEW Initialized" << std::endl;
	}

	MANAGER.Init();
	_shader = make_shared<Shader>(L"vs", L"fs");

}

static float _temp = 0.0f;
void Game::Update()
{
	MANAGER.Update();

	//cout << MANAGER.GetManager<ManagerType::Time>()->GetFps() << endl;
	_desc.clearColor.r = glm::clamp(glm::sin(_temp), 0.0f, 1.0f);
	_desc.clearColor.g = glm::clamp(glm::cos(_temp), 0.0f, 1.0f);
	_desc.clearColor.b = glm::clamp(glm::acos(_temp), 0.0f, 1.0f);

	_temp += 1.0f * MANAGER.GetManager<ManagerType::Time>()->GetDeltaTime();

	if (INPUT->GetButton(KEY_TYPE::W))
		cout << "W" << endl;
	else if (INPUT->GetButton(KEY_TYPE::A))
		cout << "A" << endl;
	else if (INPUT->GetButton(KEY_TYPE::S))
		cout << "S" << endl;
	else if (INPUT->GetButton(KEY_TYPE::D))
		cout << "D" << endl;
}
