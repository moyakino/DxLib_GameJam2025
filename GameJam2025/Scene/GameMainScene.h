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
	//オブジェクト生成処理
	//template <class T>
	//T* CreateObject(const Vector2D& location)
	//{
	//	//指定したクラスを生成する
	//	T* new_instance = new T();
	//	//GameObjectクラスを継承しているか確認
	//	GameObject* new_object = dynamic_cast<GameObject*>(new_instance);

	//	//エラーチェック
	//	if (new_object == nullptr)
	//	{
	//		delete new_instance;
	//		throw ("ゲームオブジェクトが生成できませんでした");
	//	}
};

