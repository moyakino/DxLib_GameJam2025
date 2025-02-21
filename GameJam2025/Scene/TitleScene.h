#pragma once
#include "SceneBase.h"

class TitleScene : public SceneBase
{
private:
	int background_image;
	int gametitle_image;
	int start_image;
	int ranking_image;
	int end_image;
	int end;
    int cursor_image;
	int cursor_num;
	

	int title_sound;
	int button_sound;
	int cursor_sound;

public:

	TitleScene();
	virtual ~TitleScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;
};

