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

	//現在のシーンタイプを返す
	return GetNowScene();

	/* 再設定 */
	if (fps > 59)
	{
		if (seconds > 100)
		{
			seconds = 0;
		}

		seconds++;

		/* この中に入ったら1秒たちました */
		fps = 0;
	}

}

//描画処理
void EndScene::Draw() const
{
	SetFontSize(48);
	DrawString(640, 0 + fps, "EndScene", GetColor(255, 255, 255));
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
