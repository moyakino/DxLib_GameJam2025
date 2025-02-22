#include "TitleScene.h"
#include"../Utility/InputControl.h"
#include"DxLib.h"

TitleScene::TitleScene() :background_image(NULL), gametitle1_image(NULL),gametitle2_image(NULL), cursor_image(NULL),
start_image(NULL),end_image(NULL),cursor_num(0)
{
}

TitleScene::~TitleScene()
{
}

//初期化処理
void TitleScene::Initialize()
{
	//画像の読み込み
	background_image = LoadGraph("Resource/images/background.png");
	gametitle1_image = LoadGraph("Resource/images/BANG！.png");
	gametitle2_image = LoadGraph("Resource/images/COMMAND.png");
	cursor_image = LoadGraph("Resource/images/cursor.png");
	start_image = LoadGraph("Resource/images/start.png");
	ranking_image = LoadGraph("Resource/images/ranking.png");
	end_image = LoadGraph("Resource/images/end.png");

	//BGMの読み込み
	/*title_sound = LoadSoundMem("Resource/sound/");
	button_sound = LoadSoundMem("Resource/sound/");
	cursor_sound = LoadSoundMem("Resource/sound/");*/


	end = false;

	//エラーチェック
	if (background_image == -1)
	{
		throw("Resource/images/background.pngがありません\n");
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
	if (ranking_image == -1)
	{
		throw("Resource/images/ranking.pngがありません\n");
	}
	if (end_image == -1)
	{
		throw("Resource/images/end.pngがありません\n");
	}
}

//更新処理
eSceneType TitleScene::Update()
{

	if (end == false)
	{
		//bgmが流れていなければ再生
		/*if (CheckSoundMem(title_sound) != TRUE)
		{
			PlaySoundMem(title_sound, DX_PLAYTYPE_BACK, TRUE);
		}*/

		//カーソル下移動
		if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_DOWN, 0))
		{
			/*PlaySoundMem(cursor_sound, DX_PLAYTYPE_BACK, TRUE);*/

			//カーソルの位置番号
			cursor_num++;
			//下に選択肢がないときに、上端にする
			if (cursor_num > 2)
			{
				cursor_num = 0;
			}
		}

		//カーソル上移動
		if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_UP, 0))
		{
			/*PlaySoundMem(cursor_sound, DX_PLAYTYPE_BACK, TRUE);*/

			//カーソルの位置番号
			cursor_num--;
			//上に選択肢がないときに、下端にする
			if (cursor_num < 0)
			{
				cursor_num = 2;
			}
		}

		//カーソル決定（Aボタン）（画面遷移する）
		if (InputControl::GetButtonDown(XINPUT_BUTTON_A, 0))
		{
			switch (cursor_num)
			{
			case 0:
				/*PlaySoundMem(button_sound, DX_PLAYTYPE_BACK, TRUE);*/
				return eSceneType::E_MAIN;
			case 1:
				/*PlaySoundMem(button_sound, DX_PLAYTYPE_BACK, TRUE);*/
				return eSceneType::E_RANKING;

			default:
				/*PlaySoundMem(button_sound, DX_PLAYTYPE_BACK, TRUE);*/
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
	DrawString(0, 0, "TitleScene", GetColor(255, 255, 255));

	//タイトル背景画像の描画
	DrawRotaGraph(640, 360, 1.0, 0.0, background_image, FALSE);

	//ゲームタイトルの描画
	DrawRotaGraph(330, 120, 0.74, 0.0, gametitle1_image, TRUE);
	DrawRotaGraph(920, 120, 0.70, 0.0, gametitle2_image, TRUE);

	//カーソル画像の描画
	DrawRotaGraph(400, 420 + cursor_num * 120, 0.2, 0.0, cursor_image, TRUE);

	//スタート画像の描画
	DrawRotaGraph(650, 420, 0.4, 0.0, start_image, TRUE);

	//ランキング画像の描画
	DrawRotaGraph(650, 540, 0.4, 0.0, ranking_image, TRUE);

	//エンド画像の描画
	DrawRotaGraph(650, 660, 0.4, 0.0, end_image, TRUE);
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
}

//現在のシーン情報を取得
eSceneType TitleScene::GetNowScene() const
{
	return eSceneType::E_TITLE;
}
