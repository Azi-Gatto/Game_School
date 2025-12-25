/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
/* COLLISION.cpp     																			   */
/* COLLISIONクラス																				   */

//##########ヘッダーファイル読み込み ##########
#include "COLLISION.hpp"

//########## クラスの定義 ##########

//コンストラクタ
COLLISION::COLLISION()
{
	this->SetIsDraw(true);	//当たり判定の範囲を描画する

	return;
}

//コンストラクタのオーバーロード
COLLISION::COLLISION(int left, int top, int width, int height)
{
	this->Left = left;
	this->Top = top;
	this->Width = width;
	this->Height = height;

	this->SetIsDraw(true);	//当たり判定の範囲を描画する

	return;
}


//デストラクタ
COLLISION::~COLLISION()
{
	return;
}

//四角の位置を設定
void COLLISION::SetValue(int left, int top, int width, int height)
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
int COLLISION::GetCenterX(void)
{
	return this->Left + this->Width / 2;
}

//四角の中心のY位置を取得
int COLLISION::GetCenterY(void)
{
	return this->Top + this->Height / 2;
}

//衝突検知チェック
//引　数：Collision：衝突した相手
bool COLLISION::DetectionCheck(COLLISION *aite)
{
	if (this->Top < aite->Bottom &&
		this->Left < aite->Right &&
		this->Bottom > aite->Top &&
		this->Right > aite->Left)
	{
		return true;	//当たった
	}

	return false;		//当たっていない
}

//当たり判定の範囲を描画するか
void COLLISION::SetIsDraw(bool draw)
{
	this->IsDraw = draw;
	return;
}

//当たり判定の範囲を描画
void COLLISION::Draw(void)
{
	if (this->IsDraw == true)
	{
		DrawBox(this->Left, this->Top, this->Right, this->Bottom, GetColor(255, 0, 0), false);	//枠だけ描画
	}
	return;
}

//当たり判定の範囲を描画（オーバーロード）
//引　数：unsigned int：GetColor(?,?,?)の戻り値
void COLLISION::Draw(unsigned int Color)
{
	if (this->IsDraw == true)
	{
		DrawBox(this->Left, this->Top, this->Right, this->Bottom, Color, false);	//枠だけ描画
	}
	return;
}