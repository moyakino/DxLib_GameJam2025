﻿#include "ResultScene.h"
#include"../Utility/InputControl.h"
#include"DxLib.h"

int vic_cnt1 = 0;
int vic_cnt2 = 0;
/*リザルト画面は、勝敗・コマンド入力スピードなど*/

ResultScene::ResultScene() : background_image(NULL), win_image(NULL), lose_image(NULL),win_p_image(NULL),lose_p_image(NULL),
                             result_cnt(0),result_sound(NULL)
{
	for (int i = 0; i < 5; i++)
	{
		WinLoseImage[i] = -1;
	}
}

ResultScene::~ResultScene()
{
}

//初期化処理
void ResultScene::Initialize()
{
	
	//画像の読み込み
	background_image = LoadGraph("Resource/images/bg_result.png");
	win_image = LoadGraph("Resource/images/win.png");
	lose_image = LoadGraph("Resource/images/lose.png");
	win_p_image = LoadGraph("Resource/images/player4.png");
    lose_p_image = LoadGraph("Resource/images/player3.png");

	//BGMの読み込み
	result_sound = LoadSoundMem("Resource/sound/result.wav");

	// 勝敗表示用画像の読み込み 
	WinLoseImage[0] = LoadGraph("Resource/images/0.png");
	WinLoseImage[1] = LoadGraph("Resource/images/1.png");
	WinLoseImage[2] = LoadGraph("Resource/images/2.png");
	WinLoseImage[3] = LoadGraph("Resource/images/3.png");
	WinLoseImage[4] = LoadGraph("Resource/images/(-).png");
	
	//エラーチェック
	//画像
	if (background_image == -1)
	{
		throw("Resource/images/bg_result.pngがありません\n");
	}
	if (win_image == -1)
	{
		throw("Resource/images/win.pngがありません\n");
	}
	if (lose_image == -1)
	{
		throw("Resource/images/lose.pngがありません\n");
	}
	if (win_p_image == -1)
	{
		throw("Resource/images/player4.pngがありません\n");
	}
	if (lose_p_image == -1)
	{
		throw("Resource/images/player3.pngがありません\n");
	}
}

//更新処理
eSceneType ResultScene::Update()
{
	result_cnt++;

	//3秒後にタイトルに遷移
	if (result_cnt == 180)
	{
		return eSceneType::E_TITLE;
	}
	


	//現在のシーンタイプを返す
	return GetNowScene();
}

//描画処理
void ResultScene::Draw() const
{

	//bgmが流れていなければ再生
	if (CheckSoundMem(result_sound) != TRUE)
	{
		PlaySoundMem(result_sound, DX_PLAYTYPE_BACK, TRUE);
	}

	//リザルト背景画像の描画
	DrawRotaGraph(640, 360, 1.0, 0.0, background_image, FALSE);

	//WIIN,LOSEの仮位置
	//Ｘ座標 320 or 980 , Y座標 200  0.8倍
	if (vic_cnt1 > vic_cnt2)
	{
		DrawRotaGraph(320, 200, 0.8, 0.0, win_image, TRUE);
		DrawRotaGraph(980, 200, 0.8, 0.0, lose_image, TRUE);
	}
	else
	{   
		DrawRotaGraph(980, 200, 0.8, 0.0, win_image, TRUE);
		DrawRotaGraph(320, 200, 0.8, 0.0, lose_image, TRUE);
	}
	


	//勝敗スコアの仮位置
	//Ｘ座標 530 から +120 の間隔　　 0.8倍
	DrawRotaGraph(530, 120, 0.8, 0.0, WinLoseImage[vic_cnt1], TRUE);
	DrawRotaGraph(650, 120, 0.8, 0.0, WinLoseImage[4], TRUE);
	DrawRotaGraph(770, 120, 0.8, 0.0, WinLoseImage[vic_cnt2], TRUE);
	 
	//プレイヤーの仮位置
	//X座標 350 or 960 , Y座標 470　　
	if (vic_cnt1 > vic_cnt2)
	{
		DrawRotaGraph(350, 470, 1.0, 0.0, win_p_image, TRUE,TRUE);
		DrawRotaGraph(960, 550, 0.9, 0.0, lose_p_image, TRUE , TRUE);
	}
	else
	{
		DrawRotaGraph(960, 470, 1.0, 0.0, win_p_image, TRUE,FALSE);
		DrawRotaGraph(350, 550, 0.9, 0.0, lose_p_image, TRUE,FALSE);
	}
	


}

//終了処理
void ResultScene::Finalize()
{
	vic_cnt1 = 0;
	vic_cnt2 = 0;
	DeleteGraph(background_image);
	DeleteGraph(win_image);
	DeleteGraph(lose_image);
	DeleteGraph(win_p_image);
	DeleteGraph(lose_p_image);
	
}

//現在のシーン情報を取得
eSceneType ResultScene::GetNowScene() const
{
	return eSceneType::E_RESULT;
}

void VictoryCount1(void)
{
	vic_cnt1++;
}

void VictoryCount2(void)
{
	vic_cnt2++;
}


