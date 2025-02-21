#pragma once
#define D_PIVOT_CENTER
#include<vector>
#include "SceneBase.h"
#include "../Utility/Vector2D.h"
#include "../Object/Player.h"

class GameMainScene : public SceneBase
{
private:

	Player* player;

public:

	GameMainScene();
	virtual ~GameMainScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;

private:
	
};

