#include"RankingData.h"
#include"DxLib.h"
#include<stdio.h>
#include<string.h>
#include<fstream>
#include<iostream>
#include<sstream>


RankingData::RankingData()
{
	/*for (int i = 0; i < MAXDATA; i++)
	{
		Name[i] = " ";
		VictoryNum[i] = 0;
	}

	FileOpenflg = false;
	Checkflg = false;
	FileEmptyFlg = false;*/

	
}

RankingData::~RankingData()
{

}

void RankingData::ReadRanking()
{
	std::ifstream ifs(RANKING_FILE_NAME);

	std::string line;
	for (int i = 0; std::getline(ifs, line); i++) {
		std::istringstream stream(line);
		std::string str;
		for (int j = 0; std::getline(stream, str, ','); j++) {
			if (j == 0) {
				rankingData[i].no = std::stoi(str);
			}
			else if (j == 1) {
				rankingData[i].name = str;
			}
			else {
				rankingData[i].score = std::stol(str);
			}
		}
	}
}

void RankingData::WriteRanking(std::string _name, long int stage)
{
	std::ofstream ofs(RANKING_FILE_NAME);

	rankingData[4].name = _name;
	rankingData[4].score = stage;
	for (int i = 0; i < 4; i++) {
		for (int j = i + 1; j < 5; j++) {
			if (rankingData[i].score < rankingData[j].score) {
				RANKING_DATA temp = rankingData[i];
				rankingData[i] = rankingData[j];
				rankingData[j] = temp;
			}
		}
	}

	rankingData[0].no = 1;
	for (int i = 1; i < 5; i++) {
		if (rankingData[i - 1].score == rankingData[i].score) {
			rankingData[i].no = rankingData[i - 1].no;
		}
		else {
			rankingData[i].no = i + 1;
		}
	}

	for (int i = 0; i < 5; i++) {
		ofs << rankingData[i].no << "," << rankingData[i].name.c_str() << "," << rankingData[i].score << std::endl;
	}
}

//初期化処理
//void RankingData::Initialize()
//{
//	
//
//	//ファイルオープン
//	//errno_t result = fopen_s(&fp, "Resource/dat/ranking_data.csv", "r");
//
//	//エラーチェック
//	/*if (result != 0)
//	{
//		throw("Resource/dat/ranking_data.csvが開けませんでした\n");
//	}*/
//
//	//対象ファイルから読み込む
//	/*for (int i = 0; i < 5; i++)
//	{
//		fscanf_s(fp, "%6d,%2d,%[^,],\n", &score[i], &rank[i], name[i], 15);
//	}*/
//
//	//ファイルクローズ
//	//fclose(fp);
//}

//終了処理
//void RankingData::Finalize()
//{
//
//}

//void RankingData::load(char* filename)
//{
//	string buf = "";
//	string data = "";
//
//	ifstream fileloading(filename);
//
//	//ファイルが開けているか？
//	if (!fileloading) {
//		throw("Open Not File!!");
//	}
//	else {
//		FileOpenflg = true;
//	}
//
//	if (FileOpenflg == true)
//	{
//		//getlineで行単位で読み込んでくれる
//		//
//		while (getline(fileloading, buf) && FileEmptyFlg == true)
//		{
//			//一旦ファイルのデータをコピー
//			istringstream buf_copy(buf);
//
//			////ファイルの中にデータが入っているか確認する
//			//if (buf[1] = '\0')
//			//{
//			//	FileEmptyFlg = true;
//			//}
//			//else
//			//{
//			//	FileEmptyFlg = false;
//			//}
//
//			//if (FileEmptyFlg == false)
//			//{
//
//			//}
//		}
//	}
//}

