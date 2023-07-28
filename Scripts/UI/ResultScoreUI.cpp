#include "ResultScoreUI.h"
#include "DxLib.h"
#include <string>

ResultScoreUI::ResultScoreUI(Pos position)
	: font(0)
	, score(0)
	, position()
{
	font = CreateFontToHandle("‚l‚r ƒSƒVƒbƒN", 100, 6, DX_FONTTYPE_ANTIALIASING_EDGE);
	this->position = position;
}

ResultScoreUI::~ResultScoreUI()
{
}

void ResultScoreUI::Initialize(int score)
{
	this->score = score;
}

void ResultScoreUI::Draw()
{
	DrawStringToHandle(position.x, position.y, (std::to_string(score) + "Km").c_str(), GetColor(255, 255, 255), font);
}
