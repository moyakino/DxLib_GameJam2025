#pragma once
#define D_PIVOT_CENTER
#include<vector>
#include "SceneBase.h"
#include "../Utility/Vector2D.h"
#include "../Object/Player.h"

class GameMainScene : public SceneBase
{
private:

	/* Playerオブジェクト */
	Player* player;

	/* XBoxButtonの画像 */
	int CommandButtonImage[8];
	int EmptiyImage;

	/* 乱数用 */
	int RandNum[8];
	bool RandomNumberGenerated;
	bool CommandInputFlg;

	/* コマンドの数を描画 */
	int CommandRenderCount;

	/* fps */
	int fps;

	/* カウンタ */
	int Seconds;

	/* テスト用 */
	int TestNum;

public:

	GameMainScene();
	virtual ~GameMainScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;

	void GetRandomCommand();

private:
	
};

