#include "EndScene.h"
#include"DxLib.h"

EndScene::EndScene() :location(0, 0), fps(0), seconds(0)
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
	/* フレームレート */
	fps++;


	/* 再設定 */
	if (fps > 10000)
	{
		if (seconds > 100)
		{
			seconds = 0;
		}

		seconds++;

		/* この中に入ったら1秒たちました */
		fps = 0;
	}

	//現在のシーンタイプを返す
	return GetNowScene();
}

//描画処理
void EndScene::Draw() const
{
	SetFontSize(100);

	DrawString(500, 680 - fps, "提供", GetColor(255, 255, 255));

	SetFontSize(80);
	DrawString(400, 880 - fps, "チーム社不", GetColor(255, 255, 255));

	SetFontSize(50);
	DrawString(300, 1080 - fps, "チーム社不", GetColor(255, 255, 255));

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
