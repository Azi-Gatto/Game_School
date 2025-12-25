//Mouse.cpp
//マウスの情報を管理するクラス

//############### ヘッダファイル読み込み #################
#include "Mouse.hpp"

//############### クラス定義 #################

int Mouse::LeftInfo = 0;	//左クリックの情報
int Mouse::RightInfo = 0;	//右クリックの情報

//コンストラクタ
Mouse::Mouse(){}

//デストラクタ
Mouse::~Mouse(){}

//指定された位置が、指定された領域内か確認
//戻り値: true 領域内: false 領域外
bool Mouse::HoverRect(RECT rect)
{
	int x = 0, y = 0;	//クリックされた座標
	bool f = GetPos(&x, &y);		//位置取得

	//領域内か判定
	//X座標判定
	if (rect.left <= x && rect.right >= x)
	{
		//Y座標判定
		if (rect.top <= y && rect.bottom >= y)
		{
			return true;	//領域内
		}
	}

	return false;	//領域外
}

//クリック情報更新
void Mouse::ClickUpDate()
{

	//左クリックされているときは、加算、されていない時はリセット
	(GetMouseInput() & MOUSE_INPUT_LEFT) != 0 ? ++LeftInfo : LeftInfo = 0;
	//右クリックされているときは、加算、されていない時はリセット
	(GetMouseInput() & MOUSE_INPUT_RIGHT) != 0 ? ++RightInfo : RightInfo = 0;

}

//マウスの位置を取得
bool Mouse::GetPos(int* x, int* y)
{
	//マウスの位置を取得し、成功したら、true失敗したら、falseを返す
	return GetMousePoint(x, y) == 0 ? true : false;
}

//左クリックされたか(画面内)
//戻り値: true クリックされた: false クリックされていない
bool Mouse::OnLeftClick()
{
	//クリックされた瞬間だけtrueを返す
	return LeftInfo == 1 ? true : false;
}

//左クリックされたか(指定された領域内)
//戻り値: true クリックされた: false クリックされていない
bool Mouse::OnLeftClick(RECT rect)
{
	if (HoverRect(rect))	//領域内の時
	{
		//クリックされた瞬間だけtrueを返す
		return OnLeftClick();
	}
	else //領域外の時
	{
		return false;	
	}
}

//右クリックされたか(画面内)
//戻り値: true クリックされた: false クリックされていない
bool Mouse::OnRightClick()
{
	//クリックされた瞬間だけtrueを返す
	return RightInfo == 1 ? true : false;
}

//右クリックされたか(指定された領域内)
//戻り値: true クリックされた: false クリックされていない
bool Mouse::OnRightClick(RECT rect)
{
	if (HoverRect(rect))	//領域内の時
	{
		//クリックされた瞬間だけtrueを返す
		return OnRightClick();
	}
	else //領域外の時
	{
		return false;
	}
}
