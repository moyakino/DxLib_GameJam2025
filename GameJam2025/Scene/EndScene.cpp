#include "EndScene.h"
#include"DxLib.h"

EndScene::EndScene()
{
}

EndScene::~EndScene()
{
}

//初期化処理
void EndScene::Initialize()
{
}

//更新処理
eSceneType EndScene::Update()
{
	//現在のシーンタイプを返す
	return GetNowScene();
}

//描画処理
void EndScene::Draw() const
{
	DrawString(0, 0, "EndScene", GetColor(255, 255, 255));
}

//終了処理
void EndScene::Finalize()
{
}

//現在のシーン情報を取得
eSceneType EndScene::GetNowScene() const
{
	return eSceneType::E_END;
}
