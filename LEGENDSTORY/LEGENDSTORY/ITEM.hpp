//ITEM.hpp
//アイテムクラス

#pragma once

//#################### ヘッダファイル読み込み ########################
#include "DxLib.h"
#include <vector>
#include <string>

//#################### マクロ定義 ############################
#define ITME_YAKUSOU_RECOVERY_AMOUNT 30	//薬草の回復量

#define ITEM_TYPE_HP	'H'		//アイテムタイプがHP回復の時
#define ITEM_TYPE_MP	'M'		//アイテムタイプがMP回復の時

//#################### クラス定義 ############################
class ITEM
{
private:

	std::vector<int> Code;			//アイテムコード
	std::vector<int> Possession;	//所持数
	std::vector<int> Recovery;		//回復量
	std::vector<char> ItemType;		//アイテムのタイプ

	std::vector<bool> IsDraw;		//描画してよいか

	bool Chenge_flg;				//追加したかどうか

public:

	ITEM();				//コンストラクタ

	~ITEM();			//デストラクタ

	//セッタ
	void IncreasePossession(int);	//所持数増加
	void DecreasePossession(int);	//所持数減少
	void SetRecovery(int,char);		//回復量設定
	void SetChengeFlg(bool);		//変更したか設定
	void AddItem(int,int,char);		//アイテムを追加
	void LoadData(int, int);		//セーブデータを読み込み

	//ゲッタ
	int GetCode(int);				//アイテムコード取得
	int GetPossession(int);			//所持数取得
	int GetRecovery(int);			//回復量設定
	int GetSize();					//要素数を取得
	bool GetChengeFlg(void);		//変更したか取得
	std::vector<int> GetPossession();	//所持数取得(全て)
	bool GetIsDraw(int);			//描画してよいか取得
	char GetItemType(int);			//アイテムタイプ取得

};
