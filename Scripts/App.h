#pragma once

/// <summary>
/// �A�v���P�[�V����
/// </summary>
class App
{
public:
	App();
	~App();

	void GameLoop();
private:
	class SceneManager* sceneManager;
};