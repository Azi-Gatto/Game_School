//COLLISION.hpp
//当たり判定のクラス

#pragma once

//###################### ヘッダファイル読み込み ####################
#include "DxLib.h"

//###################### マクロ定義 #######################

//###################### クラス定義 #######################
class COLLISION{
private:

	bool IsDraw;							//当たり判定の範囲を描画するか？

public:
	int Left;		//X位置
	int Top;		//Y位置
	int Width;		//幅
	int Height;		//高さ
	int Right;		//X位置＋幅
	int Bottom;		//Y位置＋高さ

public:
	COLLISION();							//コンストラクタ
	COLLISION(int, int, int, int);			//コンストラクタのオーバーロード
	virtual ~COLLISION();					//デストラクタ

	void SetValue(int, int, int, int);		//左、上、幅、高さを決定

	int GetCenterX(void);					//四角の中心のX位置を取得
	int GetCenterY(void);					//四角の中心のY位置を取得

	bool DetectionCheck(COLLISION*);		//衝突検知

	void SetIsDraw(bool);					//当たり判定の範囲を描画するか

	void Draw(void);						//当たり判定の範囲を赤色で描画
	void Draw(unsigned int);				//当たり判定の範囲の色を設定して描画

};
