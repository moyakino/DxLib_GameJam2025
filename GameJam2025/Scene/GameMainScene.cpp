#include "GameMainScene.h"
#include"../Utility/InputControl.h"
#include"DxLib.h"
#include <iostream>
#include <algorithm>
#include <random>

#include "../Object/Player.h"

GameMainScene::GameMainScene() :player(nullptr), RandomNumberGenerated(false), EmptiyImage(0), TestNum(-1), fps(0), Seconds(0), CommandInputFlg(false)
								, CurrentCommandInputCount(5)
{
	for (int i = 0; i < 8; i++)
	{
		CommandButtonImage[i] = 0;
		RandNum[i] = -1;
	}
}

GameMainScene::~GameMainScene()
{

}

//初期化処理
void GameMainScene::Initialize()
{
	/*CreateObject<Player>(Vector2D(320.0f, 94.0f));*/
	player = Player::GetInstance();
	player->Initialize(0, 0.0);

	/* XBoxButtonの画像読み込み */
	CommandButtonImage[0] = LoadGraph("Resource/images/xbox_dpad_up.png");
	CommandButtonImage[1] = LoadGraph("Resource/images/xbox_dpad_down.png");
	CommandButtonImage[2] = LoadGraph("Resource/images/xbox_dpad_left.png");
	CommandButtonImage[3] = LoadGraph("Resource/images/xbox_dpad_right.png");
	CommandButtonImage[4] = LoadGraph("Resource/images/xbox_button_a.png");
	CommandButtonImage[5] = LoadGraph("Resource/images/xbox_button_b.png");
	CommandButtonImage[6] = LoadGraph("Resource/images/xbox_button_x.png");
	CommandButtonImage[7] = LoadGraph("Resource/images/xbox_button_y.png");

	for (int i = 0; i < 8; i++)
	{
		if (CommandButtonImage[i] == -1)
		{
			throw("XBoxButtonの画像が読み込めませんでした\n");
		}
	}

	//画像読み込み
	background_image = LoadGraph("Resource/images/GameMain_Image.png");

}

//更新処理
eSceneType GameMainScene::Update()
{
	/* フレームレート */
	fps++;

	/* ランダムなコマンドを生成 */
	/* GameMainに遷移した瞬間 完了している */
	if (RandomNumberGenerated == false)
	{
		/* ランダムなコマンドを生成 */
		GetRandomCommand();

		/* 回数ごとのコマンドの数 */
		InputControl::SetCurrentCommandInputCount(0, CurrentCommandInputCount);
	}

	/* コマンド入力の受付開始 */
	/* こうしないとTitle→GameMainに遷移したときの入力が残っているため*/
	if (CommandInputFlg == true)
	{
		InputControl::SetCommandInputStart(true);
		InputControl::SetButtonNumber(0, RandNum);
		
	}

	player->Update();

	/*if (InputControl::GetButtonDown(XINPUT_BUTTON_A, 0))
	{
		return eSceneType::E_RANKING;
	}*/

	if (fps > 59)
	{
		fps = 0;

		if (RandomNumberGenerated == true)
		{
			++Seconds;
		}
		if (Seconds > 2)
		{
			Seconds = 0;
			CommandInputFlg = true;
		}
	}

	//現在のシーンタイプを返す
	return GetNowScene();
}

//描画処理
void GameMainScene::Draw() const
{
	int addx = 30;

	//背景描画
	DrawRotaGraph(640, 360, 1.0, 0.0, background_image, FALSE);
	
	/* 確認用 */
	DrawFormatString(300, 0, GetColor(255, 255, 255), "GameMain::fps::%d RandNum_ok::%d 秒数::%d", fps, RandomNumberGenerated, Seconds);
	//テスト コントローラーの入力 2Player分取得
	DrawFormatString(0, 200, GetColor(255, 255, 255),
		"Player1::%d  Player2::%d", InputControl::GetButtonDown(XINPUT_BUTTON_B, 0), InputControl::GetButtonDown(XINPUT_BUTTON_B, 1));
	DrawFormatString(1000, 300, GetColor(255, 255, 255), "RandCount %d", InputControl::GetRandCount());
	for (int i = 0; i < 8; i++)
	{
		DrawFormatString(0, 300 + i * 20, GetColor(255, 255, 255), "ランダムな数 %d \n", RandNum[i]);
		DrawFormatString(700, 300 + i * 20, GetColor(255, 255, 255), "どこが押されたか？ %d", InputControl::GetButtonNums(0, i));
	}

	/* ラウンドのコマンドの数 描画*/
	for (int i = 0; i < CurrentCommandInputCount; i++)
	{
		/* 配列で描画＆非表示を成功 */
		if ((InputControl::GetButtonNums(0, RandNum[i]) == -1))
		{
			DrawRotaGraph(50 * i + addx, 50, 0.5, 0.0, CommandButtonImage[RandNum[i]], TRUE);
		}
	}

	player->Draw();
}

//終了時処理
void GameMainScene::Finalize()
{
	/* 生成したクラスの解放 */
	delete player;

	/* 読み込んだ画像の解放 */
	for (int i = 0; i < 8; i++)
	{
		DeleteGraph(CommandButtonImage[i]);
	}
}

//現在のシーン情報を取得
eSceneType GameMainScene::GetNowScene() const
{
    return eSceneType::E_MAIN;
}

//ランダムなコマンドを出力
void GameMainScene::GetRandomCommand()
{
	/* 0 1 2 3 が デジタル方向 */
	/* 5 6 7 8 が A～Y */

	//for (int i = 0; i < 8; i++)
	//{
	//	RandNum[i] = GetRand(7);

	//	/* 最初の数を基準に再抽選 */
	//	if (i > 0)
	//	{
	//		if (RandNum[i - 1] == RandNum[i])
	//		{
	//			/* 1個前の数と現在の数が一致しなくなるまで */
	//			for (int j = i; RandNum[j - 1] == RandNum[j];)
	//			{
	//				RandNum[j] = GetRand(7);
	//			}
	//		}
	//	}
	//}

	// ランダムデバイス
	std::random_device rd;

	// メルセンヌ・ツイスター乱数生成器
	std::mt19937 gen(rd()); 

	// 0～7の数値
	int numbers[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };

	// 配列をシャッフル
	std::shuffle(std::begin(numbers), std::end(numbers), gen);

	// 0～7の要素数をランダムに決定
	std::uniform_int_distribution<int> dist(0, 7);

	// 取り出す要素数
	int count = dist(gen);

	for (int i = 0; i < 8; i++) {

		// シャッフルされた配列の先頭から count 個コピー
		RandNum[i] = numbers[i];
	}

	RandomNumberGenerated = true;
}