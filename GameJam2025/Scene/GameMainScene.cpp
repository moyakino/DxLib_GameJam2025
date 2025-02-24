﻿#include "GameMainScene.h"
#include"../Utility/InputControl.h"
#include"DxLib.h"
#include <iostream>
#include <algorithm>
#include <random>

#include "../Object/Player.h"

GameMainScene::GameMainScene() :player(nullptr), RandomNumberGenerated(false), EmptiyImage(0), TestNum(-1), fps(0), Seconds(0), CommandInputFlg(false)
								, RoundCount(5), background_image(-1), RandomNumberGenerated2(false), TestImage(0), GameRound(0)
								, PlayerWinLossCount(0), Player2WinLossCount(0), WaitTime(0), ReadyImage(0), WaitTimeStart(true), Readyflg(true)
								, ReadyImageDisplayTime(0)
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
	if (background_image == -1)
	{
		throw("background_imageの画像が読み込めませんでした\n");
	}

	//Ready画像読み込み
	ReadyImage = LoadGraph("Resource/images/ready.png");
	if (ReadyImage == -1)
	{
		throw("ReadyImageの画像が読み込めませんでした\n");
	}

	/* 最初のラウンド */
	GameRound = 0;

	/* ランダムな待ち時間を取得 */
	/* 2～4秒 */
	WaitTime = RandomWaitTime();
}

//更新処理
eSceneType GameMainScene::Update()
{
	/* フレームレート */
	fps++;

	/* メインループ (GameMain)*/
	if (GameRound < 3)
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
			/* 最初の待ち時間が終わらないとゲームが開始されない */
			if (WaitTimeStart == false)
			{
				switch (InputControl::GetCommandInputCompleted())
				{
				case 3:

					/* 勝敗判定確認中 */

					/* コマンド入力の受付開始 */
					/* こうしないとTitle→GameMainに遷移したときの入力が残っているため*/
					/* 入力受付開始したことをInputControlに送る */
					InputControl::SetCommandInputStart(true);

					/* 確認用 */
					/* 勝敗判定が終わったかどうか */
					//player->GetInputCompleteNotice(InputControl::GetCommandInputCompleted());

					break;
				case 2:
					/* Player2の勝ち*/

					/* 勝敗計算 */
					/*++Player2WinLossCount;
					if (PlayerWinLossCount != 0)
					{
						--PlayerWinLossCount;
					}*/

					/* Playerに勝敗が決まったことを通知する */
					player->GetInputCompleteNotice(InputControl::GetCommandInputCompleted());

					/* 勝敗が決まっからコントローラーの入力を受け付けない */
					InputControl::SetCommandInputStart(false);

					break;
				case 1:
					/* Player1の勝ち */

					/* 勝敗計算 */
					/*++PlayerWinLossCount;
					if (Player2WinLossCount != 0)
					{
						--Player2WinLossCount;
					}*/

					/* Playerに勝敗が決まったことを通知する */
					player->GetInputCompleteNotice(InputControl::GetCommandInputCompleted());

					/* 勝敗が決まっからコントローラーの入力を受け付けない */
					InputControl::SetCommandInputStart(false);

					break;
				case 0:
					/* 引き分け */

					player->GetInputCompleteNotice(InputControl::GetCommandInputCompleted());
					InputControl::SetCommandInputStart(false);

					break;
				default:
					break;
				}
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
			/* Readyの描画時間を決める */
			if (Readyflg == true)
			{
				++ReadyImageDisplayTime;
				/* 今は2秒たったら描画を消す */
				if (ReadyImageDisplayTime >= 2)
				{
					Readyflg = false;
				}
			}

			/* 待ち時間のカウント開始 */
			if ((Readyflg == false) && (WaitTimeStart == true))
			{
				++Seconds;
				if (WaitTime < Seconds)
				{
					/* 待ち時間が終了 */
					WaitTimeStart = false;
				}
			}
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
	
	/* 確認用 */
	//DrawFormatString(300, 700, GetColor(255, 255, 255), "GameMain::fps::%d RandNum_ok::%d RandNum2_ok::%d 秒数::%d", fps, RandomNumberGenerated, RandomNumberGenerated2,  Seconds);
	////テスト コントローラーの入力 2Player分取得
	DrawFormatString(0, 200, GetColor(255, 255, 255),
		"Player1::%d  Player2::%d", InputControl::GetButtonDown(XINPUT_BUTTON_B, 0), InputControl::GetButtonDown(XINPUT_BUTTON_B, 1));
	//DrawFormatString(500, 0, GetColor(255, 255, 255), "Player1 RandCount %d", InputControl::GetRandCount(PLAYER1));
	//DrawFormatString(500, 100, GetColor(255, 255, 255), "Player2 RandCount %d", InputControl::GetRandCount(PLAYER2));
	DrawFormatString(0, 500, GetColor(255, 255, 255), "Playwr1 Win %d", PlayerWinLossCount);
	DrawFormatString(0, 550, GetColor(255, 255, 255), "Player2 WIn %d", Player2WinLossCount);
	DrawFormatString(0, 600, GetColor(255, 255, 255), "WaitTime %d", WaitTime);
	DrawFormatString(0, 650, GetColor(255, 255, 255), "Seconds %d", Seconds);
	DrawFormatString(0, 700, GetColor(255, 255, 255), "ReadyImageDisplayTime %d", ReadyImageDisplayTime);

	for (int i = 0; i < 8; i++)
	{
		DrawFormatString(0, 0 + i * 20, GetColor(255, 255, 255), "Player1 ランダムな数 %d \n", RandNum[i]);
		DrawFormatString(200, 0 + i * 20, GetColor(255, 255, 255), "Player2 ランダムな数 %d \n", RandNum2[i]);
		DrawFormatString(700, 0 + i * 20, GetColor(255, 255, 255), "どこが押されたか？ %d", InputControl::GetButtonNums(0, i));
		DrawFormatString(900, 0 + i * 20, GetColor(255, 255, 255), "どこが押されたか？ %d", InputControl::GetButtonNums(1, i));
	}

	if (WaitTimeStart == false)
	{
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
	}

	/* Player描画 */
	player->Draw();

	/* 待ち時間の描画 */
	if (Readyflg == true)
	{
		DrawRotaGraph(640, 130, 1.2, 0.0, ReadyImage, TRUE);
	}
	
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
	/* 1秒では、速すぎるため、2～4秒に */
	int Rand = GetRand(4);
	
	if (Rand <= 1)
	{
		for (int i = 0; Rand < 2;)
		{
			Rand = GetRand(4);
		}

		return Rand;
	}
	else
	{
		/* 2 ～ 4の間で乱数生成 */
		return Rand;
	}
}

/* メインループで使っている変数を全て初期化 */
void GameMainScene::InitializeVariables()
{
	/* もう一度 乱数の生成 */
	RandomNumberGenerated = false;
	RandomNumberGenerated2 = false;

	/* Input側のランダムな数を取るのを開始 */
	InputControl::SetRandomNumber(false);

	/* ランダムな待ち時間を再設定 */
	WaitTime = RandomWaitTime();

	/* Ready画像の秒数の初期化 */
	ReadyImageDisplayTime = 0;

	/* 待ち時間の秒数の初期化*/
	Seconds = 0;

	/* Ready画像を描画開始 */
	Readyflg = true;

	/* 待ち時間を開始に設定 */
	WaitTimeStart = true;

	/* コマンドの描画数を変更 */
	/* 1ラウンド 4回 */
	/* 2ラウンド 5回 */
	/* 3ラウンド 6回 */
	RoundCount++;
}
