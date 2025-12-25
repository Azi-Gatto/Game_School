/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
/* SIKAKU.cpp     																				   */
/* SIKAKUクラス																				   */

//########## ヘッダーファイル読み込み ##########
#include "SIKAKU.hpp"

//########## クラスの定義 ##########

//コンストラクタ
SIKAKU::SIKAKU()
{
	return;
}

//コンストラクタのオーバーロード
SIKAKU::SIKAKU(int left,int top,int width,int height)
{
	this->Left = left;
	this->Top = top;
	this->Width = width;
	this->Height = height;

	return;
}

//デストラクタ
SIKAKU::~SIKAKU()
{
	return;
}

//四角の位置を設定
void SIKAKU::SetValue(int left, int top, int width, int height)
{
	this->Left = left;
	this->Top = top;
	this->Width = width;
	this->Height = height;

	this->Right = left + width;
	this->Bottom = top + height;

	return;
}

//四角の中心のX位置を取得
int SIKAKU::GetCenterX(void)
{
	return this->Left + this->Width / 2;
}

//四角の中心のY位置を取得
int SIKAKU::GetCenterY(void)
{
	return this->Top + this->Height / 2;
}
