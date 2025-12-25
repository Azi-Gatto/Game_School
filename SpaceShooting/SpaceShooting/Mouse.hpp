//Mouse.hpp
//マウスの情報を管理するクラス

#pragma once

//#################### ヘッダファイル読み込み ##################
#include "Global.hpp"

//#################### マクロ定義 ######################

//#################### クラス定義 ######################
class Mouse
{

private:

	static int LeftInfo;	//左クリックの情報
	static int RightInfo;	//右クリックの情報

public:

	Mouse();	//コンストラクタ
	~Mouse();	//デストラクタ

	static void ClickUpDate();		//クリック情報更新

	static bool GetPos(int*, int*);	//マウスの位置を取得
	static bool OnLeftClick();		//左クリックされたか(画面内)
	static bool OnLeftClick(RECT);	//左クリックされたか(指定された領域内)
	static bool OnRightClick();		//右クリックされたか(画面内)
	static bool OnRightClick(RECT);	//右クリックされたか(指定された領域内)
	static bool HoverRect(RECT);	//指定された領域内にマウスがいるか

};
