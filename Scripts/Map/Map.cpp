#include "Map.h"

Map::Map()
{
	for (int i = 0; i < 3; i++)
	{
		normalImagePos[i].x = IMAGE_WIDTH * i;
		normalImagePos[i].y = 0;
		darkerImagePos[i].x = normalImagePos[i].x;
		darkerImagePos[i].y = normalImagePos[i].y - IMAGE_HEIGHT;
		normalImage[i] = LoadGraph("Textures/Background/NormalSky.png");
		darkerImage[i] = LoadGraph("Textures/Background/DarkerSky.png");
	}
	
	sunahamImage = LoadGraph("Textures/Background/Sunahama.png");
	sprashImage = LoadGraph("Textures/Background/Water.jpg");
	alpha = 0.f;
	time = 0.f;
	speed = 600.f;//‚±‚±‚©‚¦‚é
	speedRatio = 1.f;
	addStarTimer = 0.f;
	for (int i = 0; i < 75; i++)
	{
		Star* newStar = new Star();
		stars.emplace_back(newStar);
	}
	colorScreen = MakeScreen(1920, 1080, false);
	downScaleScreen = MakeScreen(1920 / 8, 1080 / 8, false);
	gaussScreen = MakeScreen(1920 / 8, 1080 / 8, false);


	downFlag = false;
	maxTime = speed / MAX_SPEED * MAX_TIME;
	if (maxTime > 2 * DARKER_TIME)
	{
		downStartTime = maxTime - DARKER_TIME;
	}
	else
	{
		downStartTime = maxTime / 2.f;
	}

	waterY = 0.f;
}

Map::~Map()
{
}

void Map::Update(float deltaTime)
{
	time += deltaTime;
	addStarTimer += deltaTime;

	if (time > downStartTime)
	{
		downFlag = true;
	}
	if (addStarTimer > 1.f)
	{
		for (int i = 0; i < 15; i++)
		{
			Star* newStar = new Star();
			stars.emplace_back(newStar);
			addStarTimer = 0.f;
		}
	}
	for (int i = 0; i < 3; i++)
	{
		normalImagePos[i].x -= speed * deltaTime*speedRatio;
		
		if (normalImagePos[i].x < -IMAGE_WIDTH)
		{
			normalImagePos[i].x += IMAGE_WIDTH * 2;
			
		}
		darkerImagePos[i].x = normalImagePos[i].x;
		
		if (downFlag == false)
		{
			if (speed >= DARKER_MIN_SPEED && time <= NORMAL_TIME)
			{
				normalImagePos[i].y = IMAGE_HEIGHT * (1.f - (NORMAL_TIME - time) / (NORMAL_TIME)) * 0.5f;
				darkerImagePos[i].y = normalImagePos[i].y - IMAGE_HEIGHT;
			}
			else if (time > NORMAL_TIME && speed >= DARKER_MIN_SPEED)
			{
				normalImagePos[i].y = IMAGE_HEIGHT * 0.5f;
				darkerImagePos[i].y = normalImagePos[i].y - IMAGE_HEIGHT;
			}

			if (speed >= SPACE_MIN_SPEED && time <= DARKER_TIME && time > NORMAL_TIME)
			{
				alpha = (time - NORMAL_TIME) / (DARKER_TIME - NORMAL_TIME);
				normalImagePos[i].y = IMAGE_HEIGHT * (alpha * 0.5f + 0.5f);
				darkerImagePos[i].y = normalImagePos[i].y - IMAGE_HEIGHT;
			}
			else if (time >= DARKER_TIME && speed >= SPACE_MIN_SPEED)
			{
				alpha = 1.f;
				normalImagePos[i].y = IMAGE_HEIGHT;
				darkerImagePos[i].y = normalImagePos[i].y - IMAGE_HEIGHT;
			}
		}
		else
		{
			
			if (speed >= SPACE_MIN_SPEED && time < maxTime && maxTime-time>=NORMAL_TIME)
			{
				alpha = (maxTime-time-NORMAL_TIME) / (DARKER_TIME - NORMAL_TIME);
				normalImagePos[i].y = IMAGE_HEIGHT * (alpha * 0.5f + 0.5f);
				darkerImagePos[i].y = normalImagePos[i].y - IMAGE_HEIGHT;
			}
			else if (maxTime - time < NORMAL_TIME && speed >= DARKER_MIN_SPEED && time < maxTime)
			{
				alpha = 0.f;
				normalImagePos[i].y = IMAGE_HEIGHT * ((maxTime - time) / (NORMAL_TIME)) * 0.5f;
				darkerImagePos[i].y = normalImagePos[i].y - IMAGE_HEIGHT;
			}
			
		}
	}

	std::vector<Star*>deleteStar;
	for (auto ptr : stars)
	{
		if (ptr->IsEnd() == true)
		{
			deleteStar.emplace_back(ptr);
		}
	}
	for (auto ptr : deleteStar)
	{
		auto iter = std::find(stars.begin(), stars.end(), ptr);
		if (iter != stars.end())
		{
			std::iter_swap(iter, stars.end() - 1);
			stars.pop_back();
		}
	}

	for (auto ptr : stars)
	{
		ptr->Update(deltaTime);
	}
}

void Map::Draw()
{

	if (alpha != 1.f)
	{
		for (int i = 0; i < 3; i++)
		{
			DrawGraph(normalImagePos[i].x, normalImagePos[i].y, normalImage[i], true);
			DrawGraph(darkerImagePos[i].x, darkerImagePos[i].y, darkerImage[i], true);
		}
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * alpha);
		DrawBox(0, 0, 1920, 1080, GetColor(0, 0, 30), true);
		for (auto ptr : stars)
		{
			ptr->Draw(alpha);
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
	else
	{
		
		
		SetDrawScreen(colorScreen);
		ClearDrawScreen();
		DrawBox(0, 0, 1920, 1080, GetColor(0, 0, 20), true);
		for (auto ptr : stars)
		{
			ptr->Draw(alpha);
		}
		GraphFilterBlt(colorScreen, downScaleScreen, DX_GRAPH_FILTER_DOWN_SCALE, 8);
		GraphFilterBlt(downScaleScreen, gaussScreen, DX_GRAPH_FILTER_GAUSS, 16, 50);
		SetDrawScreen(DX_SCREEN_BACK);
		DrawGraph(0, 0, colorScreen, false);
		SetDrawMode(DX_DRAWMODE_ANISOTROPIC);
		SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
		DrawExtendGraph(0, 0, 1920, 1080, gaussScreen, false);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		SetDrawMode(DX_DRAWMODE_ANISOTROPIC);

	}
	
}

void Map::SetSpeed(float _speed)
{
	speed = _speed;
	maxTime = speed / MAX_SPEED * MAX_TIME;
	if (maxTime > 2*DARKER_TIME)
	{
		downStartTime = maxTime - DARKER_TIME;
	}
	else
	{
		downStartTime = maxTime / 2.f;
	}
}

void Map::Initialize()
{
	for (int i = 0; i < 3; i++)
	{
		normalImagePos[i].x = IMAGE_WIDTH * i;
		normalImagePos[i].y = 0;
		darkerImagePos[i].x = normalImagePos[i].x;
		darkerImagePos[i].y = normalImagePos[i].y - IMAGE_HEIGHT;
	}

	alpha = 0.f;
	time = 0.f;
	speed = 300.f;//‚±‚±‚©‚¦‚é
	speedRatio = 1.f;
	addStarTimer = 0.f;
	for (int i = 0; i < 75; i++)
	{
		Star* newStar = new Star();
		stars.emplace_back(newStar);
	}
	colorScreen = MakeScreen(1920, 1080, false);
	downScaleScreen = MakeScreen(1920 / 8, 1080 / 8, false);
	gaussScreen = MakeScreen(1920 / 8, 1080 / 8, false);


	downFlag = false;
	maxTime = speed / MAX_SPEED * MAX_TIME;
	if (maxTime > 2 * DARKER_TIME)
	{
		downStartTime = maxTime - DARKER_TIME;
	}
	else
	{
		downStartTime = maxTime / 2.f;
	}
}

void Map::DrawBeach()
{
	DrawGraph(0, 0, sunahamImage, false);
}

void Map::DrawWaterSprash()
{
	DrawGraph(1920 / 2 - 300, waterY+1080, sprashImage, true);
}

void Map::SprashUpdate(float deltaTime)
{
	
	if (waterY < -320.f&&sprashDownFlag==false)
	{
		sprashDownFlag = true;
	}
	if (sprashDownFlag)
	{
		waterY += deltaTime * 100;
	}
	else
	{
		waterY -= deltaTime * 100;
	}
	if (waterY > 30.f)
	{
		sprashEndFlag = true;
	}
}
