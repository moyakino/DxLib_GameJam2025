﻿#include "TitleScene.h"
#include"../Utility/InputControl.h"
#include"DxLib.h"

TitleScene::TitleScene() :background_image(NULL), gametitle1_image(NULL),gametitle2_image(NULL), cursor_image(NULL),
start_image(NULL), end_image(NULL), cursor_num(0),cursor_angle(0),holl_image(NULL),
button_sound(NULL),title_sound(NULL),cursor_sound(NULL),transition(false),ts_cnt(0)
{
}

TitleScene::~TitleScene()
{
}

//初期化処理
void TitleScene::Initialize()
{
	//画像の読み込み
	background_image = LoadGraph("Resource/images/bg_title.png");
	gametitle1_image = LoadGraph("Resource/images/BANG！.png");
	gametitle2_image = LoadGraph("Resource/images/COMMAND.png");
	cursor_image = LoadGraph("Resource/images/cursor.png");
	start_image = LoadGraph("Resource/images/start.png");
	end_image = LoadGraph("Resource/images/end.png");
	holl_image = LoadGraph("Resource/images/holl.png");

	//BGMの読み込み
	title_sound = LoadSoundMem("Resource/sound/title_bgm.wav");
	button_sound = LoadSoundMem("Resource/sound/Gunfire.wav");
	cursor_sound = LoadSoundMem("Resource/sound/cursor.wav");

	//BGMの音量設定
	ChangeVolumeSoundMem(255 * 80 / 100, title_sound);
	ChangeVolumeSoundMem(255 , button_sound);
	ChangeVolumeSoundMem(255 , cursor_sound);


	cursor_angle = 0.0;
	ts_cnt = 0;
	transition = false;

	//エラーチェック
	//画像
	if (background_image == -1)
	{
		throw("Resource/images/bg_title.pngがありません\n");
	}
	if (gametitle1_image == -1)
	{
		throw("Resource/images/.BANG！.pngがありません\n");
	}
	if (gametitle2_image == -1)
	{
		throw("Resource/images/COMMAND.pngがありません\n");
	}
	if (cursor_image == -1)
	{
		throw("Resource/images/cursor.pngがありません\n");
	}
	if (start_image == -1)
	{
		throw("Resource/images/start.pngがありません\n");
	}
	if (end_image == -1)
	{
		throw("Resource/images/end.pngがありません\n");
	}
	if (holl_image == -1)
	{
		throw("Resource/images/holl.pngがありません\n");
	}

	//サウンド
	if (button_sound == -1)
	{
		throw("Resource/images/title_bgm.wavがありません\n");
	}
	if (button_sound == -1)
	{
		throw("Resource/images/Gunfire.wavがありません\n");
	}
	if (cursor_sound == -1)
	{
		throw("Resource/images/cursor.wavがありません\n");
	}
}

//更新処理
eSceneType TitleScene::Update()
{

	if (transition == false)
	{
		//bgmが流れていなければ再生
		if (CheckSoundMem(title_sound) != TRUE)
		{
			PlaySoundMem(title_sound, DX_PLAYTYPE_BACK, TRUE);
		}

		//カーソル下移動
		if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_DOWN, 0))
		{
			PlaySoundMem(cursor_sound, DX_PLAYTYPE_BACK, TRUE);

			//カーソルの位置番号
			cursor_num++;
			//下に選択肢がないときに、上端にする
			if (cursor_num > 1)
			{
				cursor_num = 0;
			}
		}

		//カーソル上移動
		if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_UP, 0))
		{
			PlaySoundMem(cursor_sound, DX_PLAYTYPE_BACK, TRUE);

			//カーソルの位置番号
			cursor_num--;
			//上に選択肢がないときに、下端にする
			if (cursor_num < 0)
			{
				cursor_num = 1;
			}
		}

		//カーソル決定（Aボタン）（画面遷移する）
		if (InputControl::GetButtonDown(XINPUT_BUTTON_A, 0))
		{
			PlaySoundMem(button_sound, DX_PLAYTYPE_BACK, TRUE);
			cursor_angle = -0.5;
			transition = true;
		}
	}
	else
	{
		ts_cnt++;
		if (ts_cnt == 60)
		{
			switch (cursor_num)
			{
			case 0:
				return eSceneType::E_MAIN;
			default:
				return eSceneType::E_END;
			}
		}
	}

	//現在のシーンタイプを返す
	return GetNowScene();
}

//描画処理
void TitleScene::Draw() const
{
	//タイトル背景画像の描画
	DrawRotaGraph(640, 360, 1.0, 0.0, background_image, FALSE);

	//ゲームタイトルの描画
	DrawRotaGraph(330, 120, 0.74, 0.0, gametitle1_image, TRUE);
	DrawRotaGraph(920, 120, 0.70, 0.0, gametitle2_image, TRUE);

	//カーソル画像の描画
	DrawRotaGraph(400, 490 + cursor_num * 130, 0.2, cursor_angle, cursor_image, TRUE);

	//スタート画像の描画
	DrawRotaGraph(650, 490, 0.4, 0.0, start_image, TRUE);

	//エンド画像の描画
	DrawRotaGraph(650, 620, 0.4, 0.0, end_image, TRUE);

	//穴の画像の描画
	if (transition == true)
	{
		DrawRotaGraph(550, 500 + cursor_num * 130, 0.2, 0.0, holl_image, TRUE);
		DrawRotaGraph(650, 490 + cursor_num * 130, 0.3, 0.0, holl_image, TRUE);
		DrawRotaGraph(750, 460 + cursor_num * 130, 0.2, 0.0, holl_image, TRUE);
	}

	//お試し
	/*DrawRotaGraph(100, 400, 1.0, 0.0, test_image, TRUE);*/
}
	


//終了処理
void TitleScene::Finalize()
{

	DeleteGraph(background_image);
	DeleteGraph(gametitle1_image);
	DeleteGraph(gametitle2_image);
	DeleteGraph(cursor_image);
	DeleteGraph(start_image);
	DeleteGraph(end_image);
	DeleteGraph(holl_image);
	
	/*DeleteGraph(test_image);*/

	DeleteSoundMem(title_sound);
	DeleteSoundMem(button_sound);
	DeleteSoundMem(cursor_sound);
}

//現在のシーン情報を取得
eSceneType TitleScene::GetNowScene() const
{
	return eSceneType::E_TITLE;
}
