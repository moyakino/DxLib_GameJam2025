#include"RankingData.h"
#include<stdio.h>
#include<string.h>
#include<fstream>
#include<iostream>
#include<sstream>

RankingData::RankingData()
{
	for (int i = 0; i < MAXDATA; i++)
	{
		Name[i] = " ";
		VictoryNum[i] = 0;
	}

	FileOpenflg = false;
	Checkflg = false;
	FileEmptyFlg = false;
}

RankingData::~RankingData()
{

}

//初期化処理
void RankingData::Initialize()
{
	

	//ファイルオープン
	//errno_t result = fopen_s(&fp, "Resource/dat/ranking_data.csv", "r");

	//エラーチェック
	/*if (result != 0)
	{
		throw("Resource/dat/ranking_data.csvが開けませんでした\n");
	}*/

	//対象ファイルから読み込む
	/*for (int i = 0; i < 5; i++)
	{
		fscanf_s(fp, "%6d,%2d,%[^,],\n", &score[i], &rank[i], name[i], 15);
	}*/

	//ファイルクローズ
	//fclose(fp);
}

//終了処理
void RankingData::Finalize()
{

}

void RankingData::load(char* filename)
{
	string buf = "";
	string data = "";

	ifstream fileloading(filename);

	//ファイルが開けているか？
	if (!fileloading) {
		throw("Open Not File!!");
	}
	else {
		FileOpenflg = true;
	}

	if (FileOpenflg == true)
	{
		//getlineで行単位で読み込んでくれる
		//
		while (getline(fileloading, buf) && FileEmptyFlg == true)
		{
			//一旦ファイルのデータをコピー
			istringstream buf_copy(buf);

			////ファイルの中にデータが入っているか確認する
			//if (buf[1] = '\0')
			//{
			//	FileEmptyFlg = true;
			//}
			//else
			//{
			//	FileEmptyFlg = false;
			//}

			//if (FileEmptyFlg == false)
			//{

			//}
		}
	}
}

