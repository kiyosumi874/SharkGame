#include "DxLib.h"
#include "Shark.h"
#include "Common.h"
#include <math.h>

#define PI 3.141592

Shark::Shark()
{
	x = 0;
	y = 0;

	image = LoadGraph("Textures/Shark/Shark.png");
	imageAngle = 0;

	stateType = PlayerRound;
	ModeChange(Up);
}

void Shark::Update()
{	
	switch (stateType)
	{
	case Shark::PlayerRound:
		UpdatePlayerRound();
		break;
	case Shark::SharkRound:
		UpdateSharkRound();
		break;
	case Shark::End:
		break;
	default:
		break;
	}
}

void Shark::Draw()
{
	DrawRotaGraph(x,y,magnification,angle,image,true,true);
}

Shark::~Shark()
{
	DeleteGraph(image);
}

void Shark::UpdatePlayerRound()
{
	//プレイヤーの角度に基づいて回転する(とりあえず仮で設定する)
	imageAngle++;
	if (imageAngle == 24)
	{
		imageAngle = 0;//画像の角度(仮)
	}
	angle = (PI / 6) * imageAngle;
	float playerSize = 500; //プレイヤーの半径のサイズ（仮決め）

	//プレイヤーの大きさをもとに画像の表示する位置を補正
	float pxValue = cosf(angle) * playerSize;
	float pyValue = sinf(angle) * playerSize;

	x = SCREEN_WIDTH / 2 + pxValue; //SCREEN / 2 の部分はプレイヤーの中心座標
	y = SCREEN_HEIGHT / 2 + pyValue;

	//プレイヤーが手を話したらサメの初速等を設定する
	//stateType = SharkRound;
	//x = (SCREEN_WIDTH / 2) - 300;
	//y = 390;
	//ModeChange(Up);
}

void Shark::UpdateSharkRound()
{
	//モード返還（今は距離で調整）
	if (y < 400)
	{
		ModeChange(Stay);
	}
	else if(y > 600)
	{
		ModeChange(Down);
	}

	//移動
	y += flyY;

	//回転させる
	imageAngle++;
	if (imageAngle == 12)
	{
		imageAngle = 0;
	}
	angle = (PI / 6) * imageAngle;
}

void Shark::ModeChange(Mode mode)
{
	switch (mode)
	{
	case Shark::Up:
		flyY = -3;
		break;
	case Shark::Stay:
		flyY = 0.1;
		break;
	case Shark::Down:
		flyY = 3;
		break;
	default:
		break;
	}
}