#pragma once
#include<vector>
#include"DxLib.h"
#include"Star.h"

class Map
{
public:
	Map();
	virtual ~Map();

	void Update(float deltaTime);
	void Draw();
	void SetSpeed(float _speed);

private:
	struct POS
	{
		float x, y;
	};

	POS normalImagePos[3];
	POS darkerImagePos[3];
	int normalImage[3];
	int darkerImage[3];
	float alpha;
	float time;
	float speed;
	float speedRatio;
	float addStarTimer;

	std::vector<Star*>stars;

	int colorScreen;
	int downScaleScreen;
	int gaussScreen;

	const float NORMAL_TIME = 1.5f;
	const float DARKER_TIME = 10.f;
	const int IMAGE_WIDTH = 1920;
	const int IMAGE_HEIGHT = 1080;
	const float DARKER_MIN_SPEED = 100.f;
	const float SPACE_MIN_SPEED = 200.f;
};

