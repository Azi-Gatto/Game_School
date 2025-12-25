//LIST_ITEM.hpp
//LISTクラスからの派生
//アイテムの一覧を管理するクラス

#pragma once

//################### ヘッダファイル読み込み ######################
#include "LIST.hpp"

//################### マクロ定義 ####################
#define ITEM_LIST_NAME	R"(item_list.csv)"		//アイテム一覧のファイル名

#define TYPE_HP_KEY	"HP"	//アイテムタイプ判別のキーワード（HP）
#define TYPE_MP_KEY	"MP"	//アイテムタイプ判別のキーワード（MP）

//################### クラス定義 ####################
class LIST_ITEM :public LIST		//LISTクラスを継承
{
private:

	std::vector<int> Recovery;				//回復量
	std::vector<std::string> Description;	//説明文
	std::vector<char> Type;					//アイテムのタイプ

public:

	LIST_ITEM(const char *, const char *);	//コンストラクタ
	~LIST_ITEM();							//デストラクタ

	int GetRecovery(int);					//回復量取得
	const char * GetDescription(int);		//説明文取得
	char GetItemType(int);					//アイテムのタイプ取得

};
