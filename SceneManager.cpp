#include "SceneManager.h"
#include "Input.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include "ResultScene.h"

SceneManager::SceneManager()
	: currentScene(nullptr)
{
	Input::GetInstance();
}

SceneManager::~SceneManager()
{
	ClearScene();
	Input::Terminate();
}

void SceneManager::GameLoop()
{
	while (1)
	{
		if (ProcessMessage() == -1)
		{
			break;
		}
#ifdef _DEBUG
		if (Input::IsDown1P(BUTTON_ID_BACK))
		{
			break;
		}
#endif // _DEBUG


		Input::Update();

		auto tag = currentScene->Update();

		ClearDrawScreen();
		clsDx();
		currentScene->Draw();
		ScreenFlip();

		if (tag == TAG_SCENE::TAG_NONE)
		{
			continue;
		}

		ClearScene();
		if (tag == TAG_SCENE::TAG_END)
		{
			break;
		}
		SetNowScene(tag);
	}
	
}

void SceneManager::SetNowScene(const TAG_SCENE& tag)
{
	switch (tag)
	{
	case TAG_SCENE::TAG_TITLE:
		currentScene = new TitleScene();
		break;
	case TAG_SCENE::TAG_PLAY:
		currentScene = new PlayScene();
		break;
	case TAG_SCENE::TAG_RESULT:
		currentScene = new ResultScene();
		break;
	case TAG_SCENE::TAG_NONE:
		break;
	default:
		break;
	}
}

void SceneManager::ClearScene()
{
	if (currentScene != nullptr)
	{
		delete currentScene;
		currentScene = nullptr;
	}
}
