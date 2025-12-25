//Group.hpp
//複数のボタンなどを、一つのグループとして扱うためのクラス

#pragma once

//################ ヘッダファイル読み込み #################
#include "Global.hpp"
#include "Button.hpp"

//################ マクロ定義 ###################
#define CHOISE_NONE	-1				//選択していない状態

#define PAGE_START	1				//先頭のページ

using std::vector;

//################ クラス定義 ###################
class Group
{
private:

	int ElementMax;		//要素数
	RECT Area;			//領域
	vector<Button*> bt;	//ボタン

	bool IsChoise;								//選択したか
	bool IsBack;								//戻るか
	int SelectNum;								//選択したボタン

	int PageMax;								//ページ数
	int NowPage;								//現在のページ

	int DrawX;									//描画開始X位置
	int DrawY;									//描画開始Y位置
	int S_DrawX;								//描画開始X位置（最初）
	int S_DrawY;								//描画開始Y位置（最初）
	int RowNum;									//描画範囲の中で描画できる列の数
	int LineNum;								//描画範囲の中で描画できる行の数
	int Interval_Side;							//選択肢の間隔(横)
	int Interval_Vertical;						//選択肢の間隔(縦)

	void SetInit(int, int, int, int);			//初期設定


public:

	Group(Button*, int, int, int, int);			//コンストラクタ
	Group(vector<Button*>, int, int, int, int);	//コンストラクタ
	~Group();				//デストラクタ

	void SetArea(int, int, int, int);	//領域設定
	void Add(Button*);		//追加
	void Draw();			//描画
	void Clik();			//クリックしたときの処理

	bool GetIsSelect();		//選択したか
	int GetSelctNum();		//選択したボタンを取得

	bool CheckIsNextPage();	//次のページへ行けるか確認
	bool CheckIsPrevPage();	//前のページへ行けるか確認
	void NextPage();		//次のページへ
	void PrevPage();		//前のページへ
	void Reset();			//リセット

};
