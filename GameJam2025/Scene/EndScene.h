#pragma once
#include "SceneBase.h"
#include"../Utility/Vector2D.h"

#define YMAX 10000

class EndScene : public SceneBase
{
private:

	int end_thank;
	int end_you;
	int end_for;
	int end_play;
	int image_end;

	/* x y 座標 */
	Vector2D location;

	/* fps */
	int fps;

	/* カウンタ */
	int seconds;
	//時間指定お試し
	int StartTime;

public:

	EndScene();
	virtual ~EndScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;
};

