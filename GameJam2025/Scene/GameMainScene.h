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

	/* 乱数用 */
	int RandNum[8];

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

