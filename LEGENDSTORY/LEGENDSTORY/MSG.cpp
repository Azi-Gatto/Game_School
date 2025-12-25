//MSG.cpp
//メッセージクラス

//################# ヘッダファイル読み込み ######################
#include "MSG.hpp"

//################# クラス定義 ############################

//コンストラクタ
MESSAGE::MESSAGE()
{
	//初期化処理
	this->IsLastMsg = false;		//最後のメッセージではない
	this->IsMsgEnd = false;			//メッセージ描画終了ではない

	return;
}

//デストラクタ
MESSAGE::~MESSAGE()
{

	std::vector<std::string> v;			//空のvectorを作成する
	this->Msg.swap(v);					//空と中身を入れ替える

	return;
}

//文字列を設定
void MESSAGE::SetMsg(const char *msg)
{
	this->ResetFlg();					//フラグ関係リセット
	this->Msg.clear();					//中身をクリア
	this->Msg.push_back(msg);			//受け取った文字列を追加
	this->Msg_itr = this->Msg.begin();	//先頭要素のアドレスを取得
	return;
}

//文字列を追加
void MESSAGE::AddMsg(const char *msg)
{
	this->Msg.push_back(msg);		//受け取った文字列を追加
	this->Msg_itr = this->Msg.begin();	//先頭要素のアドレスを取得
	return;
}

//メッセージの内容を追加する
void MESSAGE::AddText(const char *text)
{
	this->Msg.back() += text;		//最後のメッセージに内容を追加する
	return;
}

//次のメッセージへ移動する
void MESSAGE::NextMsg(void)
{

	if (this->IsLastMsg || this->Msg.size() == 1)	//最後のメッセージを表示していたら もしくは、要素が一つしかなかったら（最初のメッセージが最後のメッセージの場合)
	{
		this->IsMsgEnd = true;	//メッセージ描画終了
	}

	if (*this->Msg_itr != this->Msg.back())			//最後のメッセージでなければ
	{
		++this->Msg_itr;	//次のメッセージへ
	}
	if(*this->Msg_itr == this->Msg.back())			//最後のメッセージだったら
	{
		this->IsLastMsg = true;	//フラグを立てる
	}

	return;
}

//前のメッセージへ移動する
void MESSAGE::BackMsg(void)
{
	if (*this->Msg_itr != this->Msg.front())		//最初のメッセージじゃなければ
	{
		--this->Msg_itr;	//前のメッセージへ
	}
}

//メッセージ描画
/*
引数：int：描画X位置
引数：int：描画Y位置
引数：unsigned int：描画色:デフォルトは白色
*/
void MESSAGE::DrawMsg(int x, int y,unsigned int color)
{
	DrawFormatString(x, y, color, "%s", this->Msg_itr->c_str());	//メッセージ描画
	return;
}

//最後のメッセージかどうか取得
bool MESSAGE::GetIsLastMsg(void)
{
	return this->IsLastMsg;
}

//空かどうか取得
bool MESSAGE::GetIsEmpty(void)
{
	return this->Msg.empty();
}

//メッセージ描画終了か取得
bool MESSAGE::GetIsMsgEnd(void)
{
	return this->IsMsgEnd;
}

//フラグ関係リセット
void MESSAGE::ResetFlg(void)
{
	this->IsLastMsg = false;	//最後のメッセージじゃない
	this->IsMsgEnd = false;		//メッセージ終了じゃない
	return;
}
