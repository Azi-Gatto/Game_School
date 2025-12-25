//EQUIPMENT.cpp
//装備関係のクラスの元になるクラス

//####################### ヘッダファイル読み込み #########################
#include "EQUIPMENT.hpp"

//####################### クラス定義 ##########################

//コンストラクタ
EQUIPMENT::EQUIPMENT()
{
	return;
}

//デストラクタ
EQUIPMENT::~EQUIPMENT()
{
	//vectorのメモリ解放を行う
	std::vector<int> v;			//空のvectorを作成する
	this->Code.swap(v);		//空と中身を入れ替える

	//vectorのメモリ解放を行う
	std::vector<int> v2;			//空のvectorを作成する
	this->Possession.swap(v2);	//空と中身を入れ替える

	//vectorのメモリ解放を行う
	std::vector<bool> v3;			//空のvectorを作成する
	this->EquipFlg.swap(v3);		//空と中身を入れ替える
	
	//vectorのメモリ解放を行う
	std::vector<bool> v4;			//空のvectorを作成する
	this->IsDraw.swap(v4);			//空と中身を入れ替える


	return;

}

//所持数増加
void EQUIPMENT::IncreasePossession(int code)
{

	for (int i = 0; i < this->GetSize(); ++i)	//リストのサイズ数分繰り返す
	{
		if (this->GetCode(i) == code)	//指定されたコードと一致したら
		{
			this->Possession[i]++;
			this->Chenge_flg = true;	//変更あり
		}
	}


	return;
}

//所持数減少
void EQUIPMENT::DecreasePossession(int code)
{
	for (int i = 0; i < this->GetSize(); ++i)	//リストのサイズ数分繰り返す
	{
		if (this->GetCode(i) == code)	//指定されたコードと一致したら
		{
			this->Possession[i]--;

			if (this->Possession[i] <= 0)	//所持数が0以下になったら
			{
				this->IsDraw[i] = false;	//描画してはいけない
			}

			this->Chenge_flg = true;		//変更あり

		}
	}


	return;
}

//装備フラグ設定
void EQUIPMENT::SetEquipFlg(int code, bool equipflg)
{

	for (int i = 0; i < this->EquipFlg.size(); ++i)	//装備数分繰り返す
	{
		this->EquipFlg[i] = false; //装備状態をすべてリセット
	}

	for (int i = 0; i < this->GetSize(); ++i)	//リストのサイズ数分繰り返す
	{
		if (this->GetCode(i) == code)	//指定されたコードと一致したら
		{
			this->EquipFlg[i] = equipflg;	//装備フラグ設定
		}
	}

	return;
}

//要素数設定
void EQUIPMENT::SetSize()
{
	this->Size = this->Code.size();	//サイズ設定
	return;
}

//装備を変更したか設定
void EQUIPMENT::SetChengeFlg(bool addflg)
{
	this->Chenge_flg = addflg;
	return;
}

//コード番号取得
int EQUIPMENT::GetCode(int kind)
{
	return this->Code[kind];
}

//装備所持数取得
int EQUIPMENT::GetPossession(int code)
{

	for (int i = 0; i < this->GetSize(); ++i)	//リストのサイズ数分繰り返す
	{
		if (this->GetCode(i) == code)	//指定されたコードと一致したら
		{
			return this->Possession[i];
		}
	}


}

//装備所持数取得
std::vector<int> EQUIPMENT::GetPossession(void)
{
	return this->Possession;	
}

//装備フラグ取得
bool EQUIPMENT::GetEquipFlg(int code)
{

	for (int i = 0; i < this->GetSize(); ++i)	//リストのサイズ数分繰り返す
	{
		if (this->GetCode(i) == code)	//指定されたコードと一致したら
		{
			return this->EquipFlg[i];
		}
	}


}

//要素数取得
int EQUIPMENT::GetSize()
{
	return this->Size;
}

//装備を追加したかどうか取得
bool EQUIPMENT::GetChengeFlg(void)
{
	return this->Chenge_flg;
}

//装備追加
/*
戻り値：true：装備が未登録だった場合
戻り値：false：装備が登録済みだった場合
*/
bool EQUIPMENT::Add(int code)
{
	//指定されたコードが既に登録されているか判定
	for (int i = 0; i < this->Code.size(); ++i)	//コード番号の数分繰り返す
	{
		if (this->Code[i] == code)	//追加されたコードがすでに登録されている場合
		{
			this->Possession[i]++;		//所持数を増加
			this->IsDraw[i] = true;			//描画してよい
			this->Chenge_flg = true;		//装備変更フラグ
			return false;					//追加処理終了(既に登録済み)
		}
	}

	//コードが登録されていなかった場合
	this->Code.push_back(code);		//コード番号追加
	this->Possession.push_back(1);	//所持数を追加（最初は1つ）
	this->EquipFlg.push_back(false);	//装備状態設定（最初は装備していない状態）
	this->Size = this->Code.size();	//要素数設定
	this->IsDraw.push_back(true);		//描画してよい
	this->Chenge_flg = true;			//装備変更フラグ

	return true;	//追加処理終了（未登録）
}

//装備情報を読み込み
void EQUIPMENT::LoadData(int code, int posse)
{
	this->Code.push_back(code);			//コード番号追加
	this->Possession.push_back(posse);	//所持数追加

	if (posse == 0)	//所持数0個だったら
	{
		this->IsDraw.push_back(false);	//描画してはいけない
	}
	else			//0個じゃなければ
	{
		this->IsDraw.push_back(true);	//描画してよい
	}

	this->EquipFlg.push_back(false);	//装備していない
	this->Size = this->Code.size();	//要素数設定
	this->Chenge_flg = true;	//変更あり

	return;

}

//描画してよいか取得
bool EQUIPMENT::GetIsDraw(int code)
{

	for (int i = 0; i < this->GetSize(); ++i)	//リストのサイズ数分繰り返す
	{
		if (this->GetCode(i) == code)	//指定されたコードと一致したら
		{
			return this->IsDraw[i];
		}
	}

}
