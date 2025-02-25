#include "ResultScene.h"
#include"../Utility/InputControl.h"
#include"DxLib.h"

/*リザルト画面は、勝敗・コマンド入力スピードなど*/

ResultScene::ResultScene() : background_image(NULL), win_image(NULL), lose_image(NULL),win_p_image(NULL),lose_p_image(NULL),
                             result_cnt(0)
{
	for (int i = 0; i < 5; i++)
	{
		WinLossImage[i] = -1;
	}
}

ResultScene::~ResultScene()
{
}

//初期化処理
void ResultScene::Initialize()
{
	background_image = LoadGraph("Resource/images/bg_result.png");
	win_image = LoadGraph("Resource/images/win.png");
	lose_image = LoadGraph("Resource/images/lose.png");
	win_p_image = LoadGraph("Resource/images/player2.png");
    lose_p_image = LoadGraph("Resource/images/player3.png");

	// 勝敗表示用画像の読み込み 
	WinLossImage[0] = LoadGraph("Resource/images/0.png");
	WinLossImage[1] = LoadGraph("Resource/images/1.png");
	WinLossImage[2] = LoadGraph("Resource/images/2.png");
	WinLossImage[3] = LoadGraph("Resource/images/3.png");
	WinLossImage[4] = LoadGraph("Resource/images/(-).png");
	
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
		throw("Resource/images/player2.pngがありません\n");
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

	if (result_cnt == 240)
	{
		return eSceneType::E_RANKING;
	}
		


	//現在のシーンタイプを返す
	return GetNowScene();
}

//描画処理
void ResultScene::Draw() const
{
	//リザルト背景画像の描画
	DrawRotaGraph(640, 360, 1.0, 0.0, background_image, FALSE);

	//
}

//終了処理
void ResultScene::Finalize()
{
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
