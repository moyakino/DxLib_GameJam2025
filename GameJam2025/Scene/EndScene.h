#pragma once
#include "SceneBase.h"
#include"../Utility/Vector2D.h"

#define YMAX 10000

class EndScene : public SceneBase
{
private:

	/* x y 座標 */
	Vector2D location;

	/* fps */
	int fps;

	/* カウンタ */
	int seconds;

public:

	EndScene();
	virtual ~EndScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;
};

