#include "GameMainScene.h"
#include"../Utility/InputControl.h"
#include"DxLib.h"
#include<random>

#include "../Object/Player.h"

GameMainScene::GameMainScene() :player(nullptr), RandomNumberGenerated(false), EmptiyImage(0), TestNum(-1), fps(0), Seconds(0)
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
}

//更新処理
eSceneType GameMainScene::Update()
{
	/* フレームレート */
	fps++;

	/* ランダムなコマンドを生成 */
	if (RandomNumberGenerated == false)
	{
		GetRandomCommand();
	}

	/* コマンド入力の受付開始 */
	/* こうしないとTitle→GameMainに遷移したときの入力が残っているため*/
	if (RandomNumberGenerated == true && Seconds > 4)
	{
		InputControl::SetCommandInputStart(true);
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
		if (Seconds > 5)
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
	int addx = 30;
	int xinputnumber[8] = { 0, 1, 2, 3, 12, 13, 14, 15 };

	//DrawFormatString(0, 0, GetColor(255, 255, 255), "%d \n", InputControl::CheckButtonRange(XINPUT_BUTTON_X));

	//テスト コントローラーの入力 2Player分取得
	DrawFormatString(0, 200, GetColor(255, 255, 255), 
		"Player1::%d  Player2::%d", InputControl::GetButtonDown(XINPUT_BUTTON_B, 0), InputControl::GetButtonDown(XINPUT_BUTTON_B, 1));

	/* 確認用 */
	DrawFormatString(300, 0, GetColor(255, 255, 255), "GameMain::fps::%d 秒数::%d", fps, Seconds);


	//DrawFormatString(700, 0, GetColor(255, 255, 255), "%d", InputControl::GetButtonNums(0, 0));

	for (int i = 0; i < 8; i++)
	{
		DrawFormatString(0, 300 + i * 20, GetColor(255, 255, 255), "%d \n", RandNum[i]);
		DrawFormatString(700, 300 + i * 20, GetColor(255, 255, 255), "%d", InputControl::GetButtonNums(0, i));

		/*if (InputControl::GetButtonNums(0, RandNum[i]) == RandNum[i])
		{
			DrawRotaGraph(50 * i + addx, 50, 0.5, 0.0, EmptiyImage, TRUE);
		}
		else
		{
			DrawRotaGraph(50 * i + addx, 50, 0.5, 0.0, CommandButtonImage[RandNum[i]], TRUE);
		}*/

		switch (RandNum[i])
		{
		case 0:
			DrawRotaGraph(50 * i + addx, 50, 0.5, 0.0, CommandButtonImage[RandNum[i]], TRUE);
			break;
		case 1:
			DrawRotaGraph(50 * i + addx, 50, 0.5, 0.0, CommandButtonImage[RandNum[i]], TRUE);
			break;
		case 2:
			DrawRotaGraph(50 * i + addx, 50, 0.5, 0.0, CommandButtonImage[RandNum[i]], TRUE);
			break;
		case 3:
			DrawRotaGraph(50 * i + addx, 50, 0.5, 0.0, CommandButtonImage[RandNum[i]], TRUE);
			break;
		case 4:
			DrawRotaGraph(50 * i + addx, 50, 0.5, 0.0, CommandButtonImage[RandNum[i]], TRUE);
			break;
		case 5:
			DrawRotaGraph(50 * i + addx, 50, 0.5, 0.0, CommandButtonImage[RandNum[i]], TRUE);
			break;
		case 6:
			DrawRotaGraph(50 * i + addx, 50, 0.5, 0.0, CommandButtonImage[RandNum[i]], TRUE);
			break;
		case 7:
			DrawRotaGraph(50 * i + addx, 50, 0.5, 0.0, CommandButtonImage[RandNum[i]], TRUE);
			break;
		default:
			break;
		}
	}

	player->Draw();
}

//終了時処理
void GameMainScene::Finalize()
{
	delete player;

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
	//std::random_device rd; //ランダムな整数を生成する(シード値)
	//std::mt19937 gen(rd());//

	/* 0 1 2 3 が デジタル方向 */
	/* 5 6 7 8 が A～Y */

	for (int i = 0; i < 8; i++)
	{
		RandNum[i] = GetRand(7);

		/* 最初の数を基準に再抽選 */
		if (i > 0)
		{
			if (RandNum[i - 1] == RandNum[i])
			{
				/* 1個前の数と現在の数が一致しなくなるまで */
				for (int j = i; RandNum[j - 1] == RandNum[j];)
				{
					RandNum[j] = GetRand(7);
				}
			}
		}
	}

	RandomNumberGenerated = true;
}

void GameMainScene::InputCommnad(int player_num)
{
	int xinputnumber[8] = { 12, 13, 14, 15, 0, 1, 2, 3 };
	
	bool flg = false;

	/*for (int i = 0; flg == InputControl::GetButtonDown(InputControl::GetButtonNums(0, xinputnumber[i]), player_num); i++)
	{
		 
	}*/
}