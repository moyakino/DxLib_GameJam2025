#pragma once
#include <string>

#define MAXDATA 255
#define RANKING_FILE_NAME "Ranking.txt"

/*名前空間*/
using namespace std;

class RankingData
{
public:

	struct RANKING_DATA {
		int  no;
		std::string name;
		long int score;
	};

	//string Name[MAXDATA];	 // 1番目 名前
	//int VictoryNum[MAXDATA]; // 2番目 勝利数
							
	//bool FileOpenflg;	//ファイルが開けているか
	//bool Checkflg;		//
	//bool FileEmptyFlg;	//ファイルの中にデータが入っているか

private:

	RANKING_DATA rankingData[5];

public:

	RankingData();		  //コンストラクタ
	~RankingData();		  //デストラクタ

	/* ランキングの読み取り */
	void ReadRanking();


	void WriteRanking(std::string _name, long int stage);

	RANKING_DATA GetRankingData(int index) { return rankingData[index]; };

	//void Initialize();    //初期化
	//void Finalize();      //終了処理

	//void load(char* filename);
};