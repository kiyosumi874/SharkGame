#include "Map.h"

Map::Map()
{
	for (int i = 0; i < 3; i++)
	{
		normalImagePos[i].x = IMAGE_WIDTH * i;
		normalImagePos[i].y = 0;
		darkerImagePos[i].x = normalImagePos[i].x;
		darkerImagePos[i].y = normalImagePos[i].y - IMAGE_HEIGHT;
		normalImage[i] = LoadGraph("Image/NormalSky.png");
		darkerImage[i] = LoadGraph("Image/DarkerSky.png");
	}
	
	alpha = 0.f;
	time = 0.f;
	speed = 500.f;//‚±‚±‚©‚¦‚é
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
}

Map::~Map()
{
}

void Map::Update(float deltaTime)
{
	time += deltaTime;
	addStarTimer += deltaTime;
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
		
		if (speed >= DARKER_MIN_SPEED&&time<=NORMAL_TIME)
		{
			normalImagePos[i].y = IMAGE_HEIGHT * (1.f - (NORMAL_TIME - time) / (NORMAL_TIME))*0.5f;
			darkerImagePos[i].y = normalImagePos[i].y - IMAGE_HEIGHT;
		}
		else if(time > NORMAL_TIME&& speed >= DARKER_MIN_SPEED)
		{
			normalImagePos[i].y = IMAGE_HEIGHT*0.5f;
			darkerImagePos[i].y = normalImagePos[i].y - IMAGE_HEIGHT;
		}

		if (speed >= SPACE_MIN_SPEED && time <= DARKER_TIME && time>NORMAL_TIME)
		{
			alpha = (time - NORMAL_TIME) / (DARKER_TIME - NORMAL_TIME);
			normalImagePos[i].y = IMAGE_HEIGHT * (alpha*0.5f+0.5f);
			darkerImagePos[i].y = normalImagePos[i].y - IMAGE_HEIGHT;
		}
		else if (time >= DARKER_TIME && speed >= SPACE_MIN_SPEED)
		{
			alpha = 1.f;
			normalImagePos[i].y = IMAGE_HEIGHT;
			darkerImagePos[i].y = normalImagePos[i].y - IMAGE_HEIGHT;
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
}
