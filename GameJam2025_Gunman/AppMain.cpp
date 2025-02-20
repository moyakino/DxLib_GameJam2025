#include "DxLib.h"
#include "ResourceManager.h"
#include "InputControl.h"
#include "Player.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPreInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	/* ウインドウモードで起動 */
	ChangeWindowMode(TRUE);

	/* Windowサイズの設定 */
	SetGraphMode(640, 480, 32);

	/* Dxlibの初期化*/
	if (DxLib_Init() == -1)
	{
		/* エラー状態を通知する */
		OutputDebugString("DXライブラリが初期化できませんでした。\n");
		return -1;
	}

	/* 描画先画面を裏にする */
	SetDrawScreen(DX_SCREEN_BACK);

	/* GameObject型の変数 objectを生成 */
	GameObject* object = nullptr;
	ResourceManager* rm = ResourceManager::GetInstance();
	int result = 0;

	try
	{
		/* プレイヤーの生成 */
		object = new Player();

		/* オブジェクトの初期化 */
		object->Initialize();

		/* メインループ */
		while (ProcessMessage() != -1)
		{
			/* 入力情報のインスタンス(オブジェクト)を取得 */
			InputControl* input = InputControl::GetInstance();

			/* キー入力情報の更新 */
			input->Update();

			/* オブジェクトの更新処理 */
			object->Update();

			/* 画面を初期化 */
			ClearDrawScreen();

			/* オブジェクトの描画処理 */
			object->Draw();

			/* 裏画面の内容を表画面に反映する */
			ScreenFlip();

			/* ESCで強制終了 */
			if (input->GetKeyUp(KEY_INPUT_ESCAPE))
			{
				break;
			}
		}
	}
	catch (std::string error_log)
	{
		/* Debug環境でのみ動作 */
		/* log.txtにエラー内容を出力する */
		OutputDebugString(error_log.c_str());

		/* 終了状態を異常に設定する */
		result = -1;
	}

	/* オブジェクトの削除 */
	if (object != nullptr)
	{
		object->Finalize();
		delete object;
		object = nullptr;
	}

	/* 入力のインスタンス(オブジェクト)を削除する */
	InputControl::DeleteInstance();

	/* 読み込んだ画像の開放 */
	rm->UnloadResourcesAll();

	/* リソース管理のインスタンス(オブジェクト)を削除する */
	ResourceManager::DeleteInstansce();

	/* ＤＸライブラリ使用の終了処理 */
	DxLib_End();

	/* 終了状態の値を返却する */
	return result;
}