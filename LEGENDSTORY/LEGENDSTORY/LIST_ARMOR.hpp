//LIST_ARMOR.hpp
//LISTクラスから派生
//防具一覧を管理するクラス

#pragma once

//################## ヘッダファイル読み込み ######################
#include "LIST.hpp"

//################## マクロ定義 ########################
#define ARMOR_LIST_NAME	R"(armor_list.csv)"		//防具一覧のファイル名

//################## クラス定義 ########################
class LIST_ARMOR :public LIST
{
private:

	std::vector<int> Defense;		//防御力

public:

	LIST_ARMOR(const char *, const char *);			//コンストラクタ
	~LIST_ARMOR();									//デストラクタ

	int GetDefense(int);							//防御力取得

};
