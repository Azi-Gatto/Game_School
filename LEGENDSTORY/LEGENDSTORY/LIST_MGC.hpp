//MGCLIST.hpp
//魔法リストのクラス


#pragma once

//################ ヘッダファイル読み込み ###################
#include "LIST.hpp"

//################ マクロ定義 #####################
#define MGC_LIST_NAME	R"(magic_list.csv)"				//魔法一覧のcsvデータの名前

//################ クラス定義 #####################
class LIST_MGC : public LIST			//リストクラスを継承
{
private:

	std::vector<int> Cost;		//消費MP

public:

	LIST_MGC(const char *,const char *);			//コンストラクタ
	~LIST_MGC();									//デストラクタ

	//ゲッタ
	int GetCost(int);			//消費MP取得
};
