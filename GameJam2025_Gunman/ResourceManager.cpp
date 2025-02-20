#include "ResourceManager.h"
#include "DxLib.h"

/* 静的メンバ変数定義 */
/* クラスのインスタンスのポインタ */
/* (クラスのオブジェクトのポインタ) */
ResourceManager* ResourceManager::instance = nullptr;

/* 役目	  リソース管理クラスのインスタンスを取得する処理 */
/* 戻り値 クラスのポインタ */
ResourceManager* ResourceManager::GetInstance()
{
	/* インスタンス(オブジェクト)が無ければ、生成する */
	if (instance == nullptr)
	{
		instance = new ResourceManager();
	}

	/* 自分自身のポインタを返却する */
	return instance;
}

/* リソース管理クラスのインスタンス(オブジェクト)を削除する処理*/
void ResourceManager::DeleteInstansce()
{
	/* インスタンス(オブジェクト)が存在していれば、削除する */
	if (instance != nullptr)
	{
		instance->UnloadResourcesAll();
		delete instance;
		instance = nullptr;
	}
}

/* 画像を取得する */
/* @param	file_name	ファイルパス */
/* @param	all_num		画像の総数 */
/* @param	num_x		横の総数 */
/* @param	num_y		縦の総数 */
/* @param	size_x		横のサイズ(px) */
/* @param	size_y		縦のサイズ(px) */
/* @return  読み込んだ画像ハンドルのstd::vector配列 */
const std::vector<int>& ResourceManager::GetImages(const std::string& file_name, int all_num, int num_x, int num_y, int size_x, int size_y)
{
	/* コンテナ内に画像が無ければ、画像を読み込む */
	if (image_container.count(file_name) == NULL)
	{
		if (all_num == 1)
		{
			CreateImagesResource(file_name);
		}
		else
		{
			CreateImagesResource(file_name, all_num, num_x, num_y, size_x, size_y);
		}
	}

	/* コンテナ内の画像データを返却 */
	return image_container[file_name];
}

const std::vector<int>& ResourceManager::GetImages(const char* file_name, int all_num, int num_x, int num_y, int size_x, int size_y)
{
	return GetImages(std::string(file_name), all_num, num_x, num_y, size_x, size_y);
}

const std::vector<int>& ResourceManager::GetImages(MaterialParam element)
{
	return GetImages(element.file_path, element.all_num, element.num_x, element.num_y, element.size_x, element.size_y);
}

int ResourceManager::GetSounds(const std::string& file_name)
{
	/* コンテナ内に音源が無ければ、音源を読み込む */
	if (sound_container[file_name] == NULL)
	{
		CreateSoundsResource(file_name);
	}

	/* コンテナ内の音源データを返却 */
	return sound_container[file_name];
}

int ResourceManager::GetSounds(const char* file_name)
{
	return GetSounds(std::string(file_name));
}

/* 全ての画像を削除する */
/* @param material_handle 削除したい画像ハンドルのstd::vector配列 */
void ResourceManager::UnloadResourcesAll()
{
	/* コンテナ内に画像が無ければ、処理を終了する */
	if (image_container.empty() == NULL)
	{
		return;
	}

	/* 全ての画像を削除 */
	for (std::pair<std::string, std::vector<int>> value : image_container)
	{
		DeleteSharingGraph(value.second[0]);
		value.second.clear();
	}

	/* 画像コンテナを解放 */
	image_container.clear();

	/* コンテナ内に音源が無ければ、処理を終了する */
	if (sound_container.empty() == NULL)
	{
		return;
	}

	/* 全ての音源の削除 */
	for (std::pair<std::string, int> value : sound_container)
	{
		DeleteSoundMem(value.second);
	}

	/* 音源コンテナを解放 */
	sound_container.clear();
}

/* 画像ハンドルを読み込みリソースを作成する */
/* @param file_name ファイルパス */
void ResourceManager::CreateImagesResource(std::string file_name)
{
	/* 指定されたファイルを読み込む */
	int handle = LoadGraph(file_name.c_str());

	/* エラーチェック */
	if (handle == -1)
	{
		throw(file_name + "がありません\n");
	}

	/* コンテナに読み込んだ画像を追加する */
	image_container[file_name].push_back(handle);
}

/* 画像ハンドルを読み込みリソースを作成する */
/* @param	file_name	ファイルパス */
/* @param	all_num		画像の総数 */
/* @param	num_x		横の総数 */
/* @param	num_y		縦の総数 */
/* @param	size_x		横のサイズ(px) */
/* @param	size_y		縦のサイズ(px) */
void ResourceManager::CreateImagesResource(std::string file_name, int all_num, int num_x, int num_y, int size_x, int size_y)
{
	/* 指定されたファイルを読み込む */
	int* handle = new int[all_num];
	int err = LoadDivGraph(file_name.c_str(), all_num, num_x, num_y, size_x, size_y, handle);

	/* エラーチェック */
	if (err == -1)
	{
		throw(file_name + "がありません\n");
	}

	/* コンテナに読み込んだ画像を追加する */
	for (int i = 0; i < all_num; i++)
	{
		image_container[file_name].push_back(handle[i]);
	}

	/* 動的メモリの開放 */
	delete[] handle;
}

/* 画像ハンドルを読み込みリソースを作成する */
void ResourceManager::CreateSoundsResource(std::string file_name)
{
	/* 指定されたファイルを読み込む */
	int handle = LoadSoundMem(file_name.c_str());

	/* エラーチェック */
	if (handle == -1)
	{
		throw(file_name + "がありません\n");
	}

	/* コンテナに読み込んだ画像を追加する */
	sound_container[file_name] = handle;
}