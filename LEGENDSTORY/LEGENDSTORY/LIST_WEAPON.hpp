//LIST_WEAPON.hpp
//リストクラスの派生
//武器の一覧を管理するクラス

#pragma once

//################# ヘッダファイル読み込み ##################
#include "LIST.hpp"

//################# マクロ定義 ###################
#define WEAPON_LIST_NAME	R"(weapon_list.csv)"		//武器一覧のファイル名

//################# クラス定義 ###################
class LIST_WEAPON :public LIST		//リストクラスから派生
{
private:

	std::vector<int> Power;			//武器の攻撃力

public:

	LIST_WEAPON(const char *,const char *);		//コンストラクタ
	~LIST_WEAPON();								//デストラクタ

	int GetPower(int);			//攻撃力取得

};
