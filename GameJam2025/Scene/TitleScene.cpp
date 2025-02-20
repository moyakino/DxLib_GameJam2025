#include "TitleScene.h"
#include"../Utility/InputControl.h"
#include"DxLib.h"

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

//初期化処理
void TitleScene::Initialize()
{
}

//更新処理
eSceneType TitleScene::Update()
{
	if (InputControl::GetButtonDown(XINPUT_BUTTON_A, 0))
	{
		return eSceneType::E_MAIN;
	}

	//現在のシーンタイプを返す
	return GetNowScene();
}

//描画処理
void TitleScene::Draw() const
{
	DrawString(0, 0, "TitleScene", GetColor(255, 255, 255));
}

//終了処理
void TitleScene::Finalize()
{
}

//現在のシーン情報を取得
eSceneType TitleScene::GetNowScene() const
{
	return eSceneType::E_TITLE;
}
