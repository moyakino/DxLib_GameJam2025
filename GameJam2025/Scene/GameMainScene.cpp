#include "GameMainScene.h"
#include"../Utility/InputControl.h"
#include"DxLib.h"

GameMainScene::GameMainScene()
{
}

GameMainScene::~GameMainScene()
{
}

//初期化処理
void GameMainScene::Initialize()
{
}

//更新処理
eSceneType GameMainScene::Update()
{
	if (InputControl::GetButtonDown(XINPUT_BUTTON_A, 0))
	{
		return eSceneType::E_RANKING;
	}

	//現在のシーンタイプを返す
	return GetNowScene();
}

//描画処理
void GameMainScene::Draw() const
{
	DrawString(0, 0, "GameMainScene", GetColor(255, 255, 255));
}

//終了時処理
void GameMainScene::Finalize()
{
}

//現在のシーン情報を取得
eSceneType GameMainScene::GetNowScene() const
{
    return eSceneType::E_MAIN;
}
