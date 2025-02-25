#include "GameMainScene.h"
#include"../Utility/InputControl.h"
#include"ResultScene.h"
#include"DxLib.h"
#include <iostream>
#include <algorithm>
#include <random>

#include "../Object/Player.h"

GameMainScene::GameMainScene() :player(nullptr), RandomNumberGenerated(false), EmptiyImage(0), TestNum(-1), fps(0), Seconds(0), CommandInputFlg(false)
								, RoundCount(5), background_image(-1), RandomNumberGenerated2(false), TestImage(0), GameRound(0)
								, PlayerWinLossCount(0), Player2WinLossCount(0), WaitTime(0), ReadyImage(0), WaitTimeStart(true), Readyflg(true)
								, ReadyImageDisplayTime(0), WinLossDisplayFlag(false), WinLossDisplayCount(0), CommandRenderFlag(false), ResultScreenTransitionCount(0)
								, FinishImage(-1), FinishRenderFlag(false), GameMain_bgm(-1)
{
	for (int i = 0; i < 8; i++)
	{
		CommandButtonImage[i] = 0;
		RandNum[i] = -1;
		RandNum2[i] = -1;
	}

	for (int i = 0; i < 5; i++)
	{
		WinLossImage[i] = -1;
	}
}

GameMainScene::~GameMainScene()
{

}

//初期化処理
void GameMainScene::Initialize()
{
	player = new Player;
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

	/* 勝敗表示用画像の読み込み */
	WinLossImage[0] = LoadGraph("Resource/images/0.png");
	WinLossImage[1] = LoadGraph("Resource/images/1.png");
	WinLossImage[2] = LoadGraph("Resource/images/2.png");
	WinLossImage[3] = LoadGraph("Resource/images/3.png");
	WinLossImage[4] = LoadGraph("Resource/images/(-).png");

	for (int i = 0; i < 5; i++)
	{
		if (CommandButtonImage[i] == -1)
		{
			throw("勝敗表示用画像が読み込めませんでした\n");
		}
	}

	//背景画像読み込み
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

	/* フィニッシュ画像読み込み */
	FinishImage = LoadGraph("Resource/images/Finish.png");
	if (FinishImage == -1)
	{
		throw("FinishImageの画像が読み込めませんでした\n");
	}

	/* BGM読み込み */
	GameMain_bgm = LoadSoundMem("Resource/sound/main_bgm.wav");
	if (GameMain_bgm == -1)
	{
		throw("GameMain_bgmの画像が読み込めませんでした\n");
	}

	/* 最初のラウンド */
	GameRound = 1;

	/* ランダムな待ち時間を取得 */
	/* 2～4秒 */
	WaitTime = RandomWaitTime();
}

//更新処理
eSceneType GameMainScene::Update()
{
	/* フレームレート */
	fps++;

	//fps % 2 == 0;

	//bgmが流れていなければ再生
	if (CheckSoundMem(GameMain_bgm) != TRUE)
	{
		PlaySoundMem(GameMain_bgm, DX_PLAYTYPE_BACK, TRUE);
	}

	/* メインループ (GameMain)*/
	if (GameRound < 4)
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

					if (Readyflg == false)
					{
						InputControl::SetCommandInputStart(true);
					}
					
					/* Playerに発射タイミングを通知 */
					//player->SetShootTiming(InputControl::GetCommandInputCompleted());

					/* 確認用 */
					/* 勝敗判定が終わったかどうか */
					//player->GetInputCompleteNotice(InputControl::GetCommandInputCompleted());

					break;
				case 2:
					/* Player2の勝ち*/

					if (WinLossDisplayFlag == false)
					{
						/* コマンド描画禁止 */
						CommandRenderFlag = false;

						/* 勝敗計算 */
						++Player2WinLossCount;
						VictoryCount2();

						/* Playerに勝敗が決まったことを通知する */
						//player->GetInputCompleteNotice(InputControl::GetCommandInputCompleted());

						/* 勝敗が決まっからコントローラーの入力を受け付けない */
						InputControl::SetCommandInputStart(false);

						/* 勝敗表示 */
						WinLossDisplayFlag = true;

						/* 再設定通知 */
						//player->SetResetflg(WinLossDisplayFlag);
					}

					break;
				case 1:
					/* Player1の勝ち */
					
					if (WinLossDisplayFlag == false)
					{
						/* コマンド描画禁止 */
						CommandRenderFlag = false;

						/* 勝敗計算 */
						++PlayerWinLossCount;
						VictoryCount1();
						/* Playerに勝敗が決まったことを通知する */
						//player->GetInputCompleteNotice(InputControl::GetCommandInputCompleted());

						/* 勝敗が決まっからコントローラーの入力を受け付けない */
						InputControl::SetCommandInputStart(false);

						/* 勝敗表示 */
						WinLossDisplayFlag = true;

						/* 再設定通知 */
						//player->SetResetflg(WinLossDisplayFlag);
					}

					break;
				case 0:
					/* 引き分け */

					if (WinLossDisplayFlag == false)
					{
						/* コマンド描画禁止 */
						CommandRenderFlag = false;

						/* Playerに勝敗が決まったことを通知する */
						player->GetInputCompleteNotice(InputControl::GetCommandInputCompleted());

						/* 勝敗が決まっからコントローラーの入力を受け付けない */
						InputControl::SetCommandInputStart(false);

						/* 勝敗表示 */
						WinLossDisplayFlag = true;

						/* 再設定通知 */
						//player->SetResetflg(WinLossDisplayFlag);
					}

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
		/* 3秒たったら画面遷移するようにする */
		/* リザルト画面に画面遷移 */

		FinishRenderFlag = true;

		if (ResultScreenTransitionCount >= 3)
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
			/* 2秒 */
			if (Readyflg == true)
			{
				++ReadyImageDisplayTime;
				/* 今は2秒たったら描画を消す */
				if (ReadyImageDisplayTime > 2)
				{
					Readyflg = false;
					WaitTimeStart = true;
					/* ランダムな待ち時間を再設定 */
					WaitTime = RandomWaitTime();
					ReadyImageDisplayTime = 0;
				}
			}

			/* 待ち時間のカウント開始 */
			/* 2 ～ 4秒 */
			if ((Readyflg == false) && (WaitTimeStart == true))
			{
				++Seconds;
				if (WaitTime < Seconds)
				{
					/* 待ち時間が終了 */
					WaitTimeStart = false;
					CommandRenderFlag = true;
					Seconds = 0;
				}
			}

			/* 勝敗表示用のカウント開始 */
			/* 3秒 */
			if (WinLossDisplayFlag == true)
			{
				if (fps < 40)
				{
					++WinLossDisplayCount;
					if (WinLossDisplayCount > 3)
					{
						WinLossDisplayFlag = false;

						/* もう一度 乱数の生成 */
						RandomNumberGenerated = false;
						RandomNumberGenerated2 = false;

						/* ラウンドを増やす*/
						++GameRound;
						++RoundCount;

						InputControl::SetRandomNumber(false);
						InputControl::SetCommandInputCompleted(false);

						WinLossDisplayCount = 0;
					}
				}
			}
		}

		if (GameRound >= 4)
		{
			++ResultScreenTransitionCount;
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

	/* RankingSceneのものが引き継がれるため */
	SetFontSize(20);

	//背景描画
	DrawRotaGraph(640, 360, 1.0, 0.0, background_image, FALSE);
	
	/* 確認用 */
	//DrawFormatString(300, 700, GetColor(255, 255, 255), "GameMain::fps::%d RandNum_ok::%d RandNum2_ok::%d 秒数::%d", fps, RandomNumberGenerated, RandomNumberGenerated2,  Seconds);
	////テスト コントローラーの入力 2Player分取得
	DrawFormatString(0, 200, GetColor(255, 255, 255),
		"Player1::%d  Player2::%d", InputControl::GetButtonDown(XINPUT_BUTTON_B, 0), InputControl::GetButtonDown(XINPUT_BUTTON_B, 1));
	//DrawFormatString(500, 0, GetColor(255, 255, 255), "Player1 RandCount %d", InputControl::GetRandCount(PLAYER1));
	//DrawFormatString(500, 100, GetColor(255, 255, 255), "Player2 RandCount %d", InputControl::GetRandCount(PLAYER2));
	//DrawFormatString(0, 500, GetColor(255, 255, 255), "Playwr1 Win %d", PlayerWinLossCount);
	DrawFormatString(0, 550, GetColor(255, 255, 255), "GameRound %d", GameRound);
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

	if (CommandRenderFlag == true)
	{
		/* ラウンドのコマンドの数 描画 Player 1 */
		for (int i = 0; i < RoundCount; i++)
		{
			/* Player1のコマンド描画 */
			if ((InputControl::GetButtonNums(PLAYER1, RandNum[i]) == -1))
			{
				DrawRotaGraph(65 * i + ROUND1XPLAYER1, 310, 0.6, 0.0, CommandButtonImage[RandNum[i]], TRUE);
			}

			/* Player2のコマンド描画 */
			if ((InputControl::GetButtonNums(PLAYER2, RandNum2[i]) == -1))
			{
				DrawRotaGraph(65 * i + 900, 310, 0.6, 0.0, CommandButtonImage[RandNum2[i]], TRUE);
			}
		}
	}

	/* Player描画 */
	player->Draw();

	/* Readyの描画 */
	if (Readyflg == true)
	{
		DrawRotaGraph(640, 130, 1.2, 0.0, ReadyImage, TRUE);
	}

	/* 勝敗の表示 */
	if (WinLossDisplayFlag == true)
	{
		/* 点滅 */
		if (fps < 40)
		{
			/* Player1の勝敗 */
			DrawRotaGraph(400, 260, 1.5, 0.0, WinLossImage[PlayerWinLossCount], TRUE);

			/* ハイフン ( - ) */
			DrawRotaGraph(620, 260, 1.5, 0.0, WinLossImage[4], TRUE);

			/* Player2の勝敗 */
			DrawRotaGraph(830, 260, 1.5, 0.0, WinLossImage[Player2WinLossCount], TRUE);
		}
	}

	if (FinishRenderFlag == true)
	{
		DrawRotaGraph(630, 130, 1.2, 0.0, FinishImage, TRUE);
	}
}

//終了時処理
void GameMainScene::Finalize()
{

	/* ここらへん */

	/* 生成したクラスの解放 */
	player->Finalize();
	delete player;

	/* 読み込んだ画像の解放 */
	for (int i = 0; i < 8; i++)
	{
		DeleteGraph(CommandButtonImage[i]);
	}

	for (int i = 0; i < 5; i++)
	{
		DeleteGraph(WinLossImage[i]);
	}

	DeleteGraph(ReadyImage);
	DeleteGraph(FinishImage);
	DeleteGraph(ReadyImage);
	DeleteSoundMem(GameMain_bgm);
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

	if ((RandomNumberGenerated == true) && (RandomNumberGenerated2 == true))
	{
		Readyflg = true;
	}
}

bool GameMainScene::GetWinLossDisplayFlag()
{
	return WinLossDisplayFlag;
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

	

	/* Ready画像の秒数の初期化 */
	ReadyImageDisplayTime = 0;

	/* 待ち時間の秒数の初期化*/
	Seconds = 0;

	/* Ready画像を描画開始 */
	Readyflg = true;

	/* 待ち時間を開始に設定 */
	WaitTimeStart = true;

	/* コマンドの描画開始に設定 */
	/* コマンド描画禁止 */
	CommandRenderFlag = true;

	/* コマンドの描画数を変更 */
	/* 1ラウンド 4回 */
	/* 2ラウンド 5回 */
	/* 3ラウンド 6回 */
	RoundCount++;
}
