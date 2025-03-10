﻿#pragma once
#include "SceneBase.h"


void VictoryCount1(void);
void VictoryCount2(void);

class ResultScene : public SceneBase
{
private:
	//背景画像
	int background_image;

	//Win,Loseのテキスト画像
	int win_image;
	int lose_image;
	
	//プレイヤー画像
	int win_p_image;
	int lose_p_image;

	//勝敗用
	int WinLoseImage[5];
	
	//タイトルに遷移するまでのカウント
	int result_cnt;

	int result_sound;
	

	
	


public:

	ResultScene();
	virtual ~ResultScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;

};

