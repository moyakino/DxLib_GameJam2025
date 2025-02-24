#include "GameMainScene.h"
#include"../Utility/InputControl.h"
#include"DxLib.h"
#include <iostream>
#include <algorithm>
#include <random>

#include "../Object/Player.h"

GameMainScene::GameMainScene() :player(nullptr), RandomNumberGenerated(false), EmptiyImage(0), TestNum(-1), fps(0), Seconds(0), CommandInputFlg(false)
								, RoundCount(7), background_image(-1), RandomNumberGenerated2(false), ImagePosX(0), ImagePosY(0), TestImage(0), GameRound(0)
{
	for (int i = 0; i < 8; i++)
	{
		CommandButtonImage[i] = 0;
		RandNum[i] = -1;
		RandNum2[i] = -1;
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

	/* 最初のラウンド */
	GameRound = 1;
}

//更新処理
eSceneType GameMainScene::Update()
{
	/* フレームレート */
	fps++;

	/* メインループ (GameMain)*/
	if (GameRound != 4)
	{
		/* ランダムなコマンドを生成 */
		/* GameMainに遷移した瞬間 完了している */
		if (RandomNumberGenerated == false && RandomNumberGenerated2 == false)
		{
			if (RandomNumberGenerated == false)
			{
				/* Player1用 */
				/* ランダムなコマンドを生成 */
				GetRandomCommand(PLAYER1);

				/* 回数ごとのコマンドの数 */
				InputControl::SetCurrentCommandInputCount(PLAYER1, RoundCount);

				/* 生成した配列をInputControlに送る */
				InputControl::SetButtonNumber(PLAYER1, RandNum);
			}
			if (RandomNumberGenerated2 == false)
			{
				/* Player2用 */
				/* ランダムなコマンドを生成 */
				GetRandomCommand(PLAYER2);

				/* 回数ごとのコマンドの数 */
				InputControl::SetCurrentCommandInputCount(PLAYER2, RoundCount);

				/* 生成した配列をInputControlに送る */
				InputControl::SetButtonNumber(PLAYER2, RandNum2);
			}
		}
		else
		{
			/* 勝敗判定が動いたら全てを初期化・再生成 */
			if (InputControl::GetCommandInputCompleted() == 3)
			{
				/* コマンド入力の受付開始 */
				/* こうしないとTitle→GameMainに遷移したときの入力が残っているため*/
				/* 入力受付開始したことをInputControlに送る */
				InputControl::SetCommandInputStart(true);
			}
			else
			{
				InputControl::SetCommandInputStart(false);
			}
		}
	}
	else
	{
		/* Player1だけの入力を確認 */
		/* リザルト画面に画面遷移 */
		if (InputControl::GetButtonDown(XINPUT_BUTTON_A, 0))
		{	
			return eSceneType::E_RESULT;
		}
	}

	player->Update();

	

	if (fps > 59)
	{
		fps = 0;

		/* ランダムな数の生成が完了 */
		if (RandomNumberGenerated == true && RandomNumberGenerated2 == true)
		{
			++Seconds;
		}
		if (Seconds > 2)
		{
			Seconds = 0;
		}
	}

	//現在のシーンタイプを返す
	return GetNowScene();
}

//描画処理
void GameMainScene::Draw() const
{
	/* 30 倍率 0.5 */
	/* x 50 * i + addx */
	int addx = 30;

	//背景描画
	DrawRotaGraph(640, 360, 1.0, 0.0, background_image, FALSE);

	//DrawRotaGraph(0, 0, 1.0, 0.0, TestImage, FALSE);
	
	/* 確認用 */
	DrawFormatString(300, 700, GetColor(255, 255, 255), "GameMain::fps::%d RandNum_ok::%d RandNum2_ok::%d 秒数::%d", fps, RandomNumberGenerated, RandomNumberGenerated2,  Seconds);
	//テスト コントローラーの入力 2Player分取得
	DrawFormatString(0, 200, GetColor(255, 255, 255),
		"Player1::%d  Player2::%d", InputControl::GetButtonDown(XINPUT_BUTTON_B, 0), InputControl::GetButtonDown(XINPUT_BUTTON_B, 1));
	DrawFormatString(500, 0, GetColor(255, 255, 255), "Player1 RandCount %d", InputControl::GetRandCount(PLAYER1));
	DrawFormatString(500, 100, GetColor(255, 255, 255), "Player2 RandCount %d", InputControl::GetRandCount(PLAYER2));

	for (int i = 0; i < 8; i++)
	{
		DrawFormatString(0, 0 + i * 20, GetColor(255, 255, 255), "Player1 ランダムな数 %d \n", RandNum[i]);
		DrawFormatString(200, 0 + i * 20, GetColor(255, 255, 255), "Player2 ランダムな数 %d \n", RandNum2[i]);
		DrawFormatString(700, 0 + i * 20, GetColor(255, 255, 255), "どこが押されたか？ %d", InputControl::GetButtonNums(0, i));
		DrawFormatString(900, 0 + i * 20, GetColor(255, 255, 255), "どこが押されたか？ %d", InputControl::GetButtonNums(1, i));
	}

	/* ラウンドのコマンドの数 描画 Player 1 */
	for (int i = 0; i < RoundCount; i++)
	{
		/* 配列で描画＆非表示を成功 */
		if ((InputControl::GetButtonNums(PLAYER1, RandNum[i]) == -1))
		{
			DrawRotaGraph(65 * i + ROUND1XPLAYER1, 310, 0.6, 0.0, CommandButtonImage[RandNum[i]], TRUE);
		}

		/* 配列で描画＆非表示を成功 */
		if ((InputControl::GetButtonNums(PLAYER2, RandNum2[i]) == -1))
		{
			DrawRotaGraph(65 * i + 970, 310, 0.6, 0.0, CommandButtonImage[RandNum2[i]], TRUE);
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
void GameMainScene::GetRandomCommand(int player_num)
{
	/* 0 1 2 3 が デジタル方向 */
	/* 5 6 7 8 が A～Y */

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

	if (player_num == PLAYER1)
	{
		for (int i = 0; i < 8; i++) {

			// シャッフルされた配列の先頭から count 個コピー
			RandNum[i] = numbers[i];
		}

		RandomNumberGenerated = true;
	}
	else if (player_num == PLAYER2)
	{
		for (int i = 0; i < 8; i++) {

			// シャッフルされた配列の先頭から count 個コピー
			RandNum2[i] = numbers[i];
		}

		RandomNumberGenerated2 = true;
	}
	
}

int GameMainScene::RandomWaitTime()
{
	/*int Rand = GetRand(3);
	
	if (Rand == 0)
	{
		for (int i = 3; Rand != ;)
		{

		}
	}*/

	return 0;
}
