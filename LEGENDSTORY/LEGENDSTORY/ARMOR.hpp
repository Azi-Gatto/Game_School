//ARMOR.hpp
//EQUIPMENTクラスから派生
//防具を管理するクラス

#pragma once

//###################### ヘッダファイル読み込み ######################
#include "EQUIPMENT.hpp"

//###################### マクロ定義 ###########################

//###################### クラス定義 ###########################
class ARMOR :public EQUIPMENT		//EQUIPMENTクラスから派生
{
private:

	std::vector<int> Def;		//防御力

public:

	ARMOR();			//コンストラクタ
	~ARMOR();			//デストラクタ

	void SetDef(int);	//防御力を設定
	int GetDef(int);	//防御力を取得

};

