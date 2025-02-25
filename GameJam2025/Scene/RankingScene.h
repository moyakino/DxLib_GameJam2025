﻿#pragma once
#include "SceneBase.h"
#include "../Object/RankingData.h"

class RankingScene : public SceneBase
{
private:

	//RankingData* rankingdata;

	RankingData ranking;
	RankingData::RANKING_DATA rankingData[5];

	/*int image;
	int bgm;
	int TitleSE2;

	int DesideSE;*/


public:

	RankingScene();
	virtual ~RankingScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;
};

