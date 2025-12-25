//LIST.hpp
//スキルや魔法の一覧を管理するクラス

/*
追加方法
・このクラスは、一覧を管理する基になるクラスのため、データの読み込みなどは、派生させたクラスで行う
　例：武器の一覧データを読み込むのは、派生クラスである、LIST_WEAPONクラスで行う。
・派生クラスでは、内容によって必要な要素を追加する
　例：武器一覧なら、攻撃力、防具一覧なら、防御力など
*/

#pragma once

//################ ヘッダファイル読み込み ######################
#include "DxLib.h"
#include <vector>
#include <string>
#include <fstream>

//################ マクロ定義 #########################
#define LIST_DIR		R"(.\MY_DATA\List\)"			//リストのディレクトリ名

//############## マクロ定義：エラーメッセージ ###################
#define LIST_ERROR_TTILE	"LIST_ERROR"						//エラータイトル
#define LIST_ERROR_MSG		"リストが読み込めませんでした"		//エラーメッセージ

//################ クラス定義 #########################
class LIST
{
private:

	std::vector <std::string> Name;		//名前

	std::vector<int> Code;				//コード番号

	int Size;							//リストの要素数

	bool IsLoad;						//読み込めたか

public:	

	LIST();								//コンストラクタ
	~LIST();							//デストラクタ

	//セッタ
	void SetName(std::string);			//名前設定
	void SetCode(int);					//コード番号設定
	void SetSize();						//リストの要素数設定
	void SetIsLoad(bool);				//読み込めたか設定

	//ゲッタ
	const char * GetName(int);			//技名取得
	bool GetIsLoad(void);				//読み込めたか
	int GetListSize(void);				//リストの要素数を取得
	int GetCode(int);					//コード番号取得

};
