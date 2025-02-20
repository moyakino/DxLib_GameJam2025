#include "ResultScene.h"
#include"../Utility/InputControl.h"
#include"DxLib.h"

/*リザルト画面は、勝敗・コマンド入力スピードなど*/

ResultScene::ResultScene()
{
}

ResultScene::~ResultScene()
{
}

//初期化処理
void ResultScene::Initialize()
{
}

//更新処理
eSceneType ResultScene::Update()
{
	if (InputControl::GetButtonDown(XINPUT_BUTTON_A, 0))
	{
		return eSceneType::E_END;
	}

	//現在のシーンタイプを返す
	return GetNowScene();
}

//描画処理
void ResultScene::Draw() const
{
	DrawString(0, 0, "ResultScene", GetColor(255, 255, 255));
}

//終了処理
void ResultScene::Finalize()
{
}

//現在のシーン情報を取得
eSceneType ResultScene::GetNowScene() const
{
	return eSceneType::E_RESULT;
}
