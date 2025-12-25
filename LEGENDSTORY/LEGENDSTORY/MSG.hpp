//MSG.hpp
//メッセージクラス

#pragma once

//################ ヘッダファイル読み込み ##################
#include "DxLib.h"
#include "main.hpp"
#include "UI.hpp"
#include "PLAYER.hpp"
#include "ENEMY.hpp"

//################ マクロ定義 ####################
#define BT_MSG_DRAW_X 20	//戦闘画面のメッセージの描画位置(X)
#define BT_MSG_DRAW_Y 400	//戦闘画面のメッセージの描画位置(Y)

#define BT_MSG_KIND	2	//メッセージの種類

//################ 列挙型 ########################
enum BT_MSG_TYPE
{
	BT_MSG_ACT,		//バトルメッセージ
	BT_MSG_RESULT	//リザルトメッセージ
};//戦闘画面でのメッセージの種類

//################ クラス定義 ####################
class MESSAGE
{
private:

	std::vector<std::string> Msg;		//メッセージ格納用
	std::vector<std::string>::iterator Msg_itr;	//Msgのイテレータ

	bool IsLastMsg;	//最後のメッセージか
	bool IsMsgEnd;	//メッセージ描画終了か

public:

	MESSAGE();		//コンストラクタ

	~MESSAGE();		//デストラクタ

	void SetMsg(const char *);			//メッセージを設定する
	void AddMsg(const char *);			//メッセージを追加する
	void AddText(const char *);			//メッセージの内容を追加する
	void NextMsg(void);					//次のメッセージへ移動する
	void BackMsg(void);					//前のメッセージへ移動する

	void DrawMsg(int, int,unsigned int);	//メッセージ描画
	bool GetIsLastMsg(void);				//最後のメッセージかどうか取得
	bool GetIsEmpty(void);					//空かどうか取得
	bool GetIsMsgEnd(void);					//メッセージ描画終了か取得
	void ResetFlg(void);					//フラグ関係リセット

};
