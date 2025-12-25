/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
/* SIKAKU.hpp     																				   */
/* SIKAKUクラス																					   */

#pragma once

//########## ヘッダーファイル読み込み ##########

//########## マクロ定義 ##########

//########## クラスの定義 ##########

class SIKAKU
{
public:
	int Left;		//X位置
	int Top;		//Y位置
	int Width;		//幅
	int Height;		//高さ
	int Right;		//X位置＋幅
	int Bottom;		//Y位置＋高さ

public:
	SIKAKU();					//コンストラクタ
	SIKAKU(int, int, int, int);	//コンストラクタのオーバーロード
	virtual ~SIKAKU();	//デストラクタ

	void SetValue(int, int, int, int);	//左、上、幅、高さを決定

	int GetCenterX(void);	//四角の中心のX位置を取得
	int GetCenterY(void);	//四角の中心のY位置を取得

};

