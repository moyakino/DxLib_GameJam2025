#pragma once
#include <string>

#define MAXDATA 255

/*名前空間*/
using namespace std;

class RankingData
{
private:

	string Name[MAXDATA];	 // 1番目 名前
	int VictoryNum[MAXDATA]; // 2番目 勝利数
							
	bool FileOpenflg;	//ファイルが開けているか
	bool Checkflg;		//
	bool FileEmptyFlg;	//ファイルの中にデータが入っているか

public:

	RankingData();		  //コンストラクタ
	~RankingData();		  //デストラクタ

	void Initialize();    //初期化
	void Finalize();      //終了処理

	void load(char* filename);

public:
	

};