#pragma once
#define D_PIVOT_CENTER
#include<vector>
#include "SceneBase.h"
#include "../Utility/Vector2D.h"
#include "../Object/Player.h"

#define PLAYER1 0
#define PLAYER2 1

#define ROUND1X 30

class GameMainScene : public SceneBase
{
private:

	/* Playerオブジェクト */
	Player* player;

	/* XBoxButtonの画像 */
	int CommandButtonImage[8];
	int EmptiyImage;

	/* 乱数用 Player1 用 */
	int RandNum[8];

	/* 乱数用 Player2 用 */
	int RandNum2[8];

	bool RandomNumberGenerated;
	bool RandomNumberGenerated2;
	bool CommandInputFlg;

	/* コマンドの数を描画 */
	int RoundCount;

	/* ラウンド用画像*/
	int ImagePosX;
	int ImagePosY;

	/* fps */
	int fps;

	/* カウンタ */
	int Seconds;

	/* テスト用 */
	int TestNum;
	int TestImage;

	//背景
	int background_image;

public:

	GameMainScene();
	virtual ~GameMainScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;

	void GetRandomCommand(int player_num);

private:
	
};

