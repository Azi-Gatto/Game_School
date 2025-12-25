//WEAPON.hpp
//EQUIPMENTクラスの派生
//装備の中の武器を管理するクラス

#pragma once

//################ ヘッダファイル読み込み #################
#include "EQUIPMENT.hpp"

//################ マクロ定義 ####################

//################ クラス定義 ####################
class WEAPON :public EQUIPMENT	//EQUIPMENTクラスを継承
{
private:

	std::vector<int> Atk;		//武器の攻撃力

public:

	WEAPON();					//コンストラクタ
	~WEAPON();					//デストラクタ

	void SetAtk(int);			//攻撃力を設定

	int GetAtk(int);			//攻撃力を取得

};
