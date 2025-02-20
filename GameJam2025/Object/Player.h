#pragma once
#include"../Utility/Vector2D.h"

class Player
{
private:




public:
	Player();	//コンストラクタ
	~Player();	//デストラクタ

	void Initialize(int pnum, float x);         //初期化処理
												// pnumは何番目のPlayerなのか？
												// x はPlayerのx座標

	void Update();								//更新処理
	void Draw()const;							//描画処理
	void Finalize();							//終了時処理

};

