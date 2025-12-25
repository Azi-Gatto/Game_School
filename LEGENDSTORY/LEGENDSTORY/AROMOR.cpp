//AROMOR.cpp
//EQUIPMENTクラスから派生
//防具を管理するクラス

//##################### ヘッダファイル読み込み ###################
#include "ARMOR.hpp"

//##################### クラス定義 ##########################

//コンストラクタ
ARMOR::ARMOR()
{
	return;
}

//デストラクタ
ARMOR::~ARMOR()
{
	//vectorのメモリ解放を行う
	std::vector<int> v;			//空のvectorを作成する
	this->Def.swap(v);			//空と中身を入れ替える

	return;
}

//防御力を設定
void ARMOR::SetDef(int def)
{
	this->Def.push_back(def);
	return;
}

//防御力を取得
int ARMOR::GetDef(int code)
{

	for (int i = 0; i < this->GetSize(); ++i)	//リストのサイズ数分繰り返す
	{
		if (this->GetCode(i) == code)	//指定されたコードと一致したら
		{
			return this->Def[i];
		}
	}

}
