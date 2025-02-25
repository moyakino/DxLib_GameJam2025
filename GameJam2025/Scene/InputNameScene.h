#pragma once
#include "SceneBase.h"
//#include "Ranking.h"
#include"../Object/RankingData.h"
#include "DxLib.h"

class InputNameScene : public SceneBase
{
private:

	RankingData ranking;
	RankingData::RANKING_DATA rankingData[5];

	int score;
	std::string name;

	POINT cursorPoint;
	const char keyboard[5][14] = { "ABCDEFGHIJKLM" ,"NOPQRSTUVWXYZ" ,"abcdefghijklm" ,"nopqrstuvwxyz" ,"0123456789<" };

public:

	InputNameScene();
	virtual ~InputNameScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;
};

