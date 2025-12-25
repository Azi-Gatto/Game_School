//Group.cpp

//############## ヘッダファイル読み込み ###############
#include "Group.hpp"

//############## クラス定義 #################

//コンストラクタ
/*
引数：Button*：グループに追加するボタン
引数：int：x位置
引数：int：y位置
引数：int：横の間隔
引数：int：縦の間隔
*/
Group::Group(Button* bt,int x, int y, int side,int vertical)
{
	//メンバー初期化
	Area = { 0 };			//領域
	IsChoise = false;		//選択したか
	PageMax = 0;			//ページ数
	NowPage = PAGE_START;	//現在のページ
	DrawX = 0;				//描画開始X位置
	DrawY = 0;				//描画開始Y位置
	S_DrawX = 0;			//描画開始X位置(Init)
	S_DrawY = 0;			//描画開始Y位置(Init)
	RowNum = 0;				//描画範囲の中で描画できる列の数
	LineNum = 0;			//描画範囲の中で描画できる行の数
	Interval_Side = 0;		//選択肢の間隔(横)
	Interval_Vertical = 0;	//選択肢の間隔(縦)
	SelectNum = -1;			//選択したボタン

	this->bt.push_back(bt);	//ボタン追加

	SetInit(x, y, side, vertical);	//初期設定


}

//コンストラクタ
/*
引数：vector<Button*>：グループに追加するボタン
引数：int：x位置
引数：int：y位置
引数：int：横の間隔
引数：int：縦の間隔
*/
Group::Group(vector<Button*> bt, int x, int y, int side, int vertical)
{
	//メンバー初期化
	Area = { 0 };			//領域
	IsChoise = false;		//選択したか
	PageMax = 0;			//ページ数
	NowPage = PAGE_START;	//現在のページ
	DrawX = 0;				//描画開始X位置
	DrawY = 0;				//描画開始Y位置
	S_DrawX = 0;			//描画開始X位置(Init)
	S_DrawY = 0;			//描画開始Y位置(Init)
	RowNum = 0;				//描画範囲の中で描画できる列の数
	LineNum = 0;			//描画範囲の中で描画できる行の数
	Interval_Side = 0;		//選択肢の間隔(横)
	Interval_Vertical = 0;	//選択肢の間隔(縦)
	SelectNum = -1;			//選択したボタン

	this->bt = bt;			//ボタン追加
	ElementMax = this->bt.size();	//要素数設定

	SetInit(x, y, side, vertical);	//初期設定

}

//初期設定
/*
引数：int：x位置
引数：int：y位置
引数：int：横の間隔
引数：int：縦の間隔
*/
void Group::SetInit(int x, int y, int side, int vertical)
{
	DrawX = x;				//描画開始X位置設定
	DrawY = y;				//描画開始Y位置設定
	S_DrawX = x;			//描画開始X位置(Init)
	S_DrawY = y;			//描画開始Y位置(Init)
	Interval_Side = side;	//選択肢の間隔(横)を設定
	Interval_Vertical = vertical;	//選択肢の間隔(縦)を設定

	SetArea(x, y, GAME_WIDTH, GAME_HEIGHT);	//領域を設定

	//描画範囲の中で描画できる列の数を計算
	while (true)	//無限ループ
	{

		if (x + bt.at(RowNum)->GetWidth() + side <= GAME_WIDTH)	//画面内なら
		{
			x += bt.at(RowNum)->GetWidth() + side;	//Xの位置をずらす
			++RowNum;	//カウントアップ
		}
		else	//画面外なら
		{
			break;	//ループ終了
		}

		if (RowNum > bt.size() - 1)	//ボタンの数分、処理が終わったら
			break;						//ループ終了
	}

	//描画範囲の中で描画できる行の数を計算
	while (true)	//無限ループ
	{		

		if (y + bt.at(LineNum)->GetHeight() <= GAME_HEIGHT)	//画面内なら
		{
			y += bt.at(LineNum)->GetHeight() + vertical;	//yの位置をずらす
			++LineNum;	//カウントアップ
		}
		else	//画面外なら
		{
			break;	//ループ終了
		}

		if (LineNum > bt.size() - 1)	//ボタンの数分、処理が終わったら
			break;						//ループ終了

	}

	//選択肢をすべて描画するのに、何ページ必要か計算
	int one_page = RowNum * LineNum;	//1ページに入る選択肢の数
	do
	{
		++PageMax;	//ページ数増加
	} while ((one_page * PageMax) < bt.size());
	NowPage = PAGE_START;	//先頭のページを現在のページに設定

}

//デストラクタ
Group::~Group()
{
	for (auto b : bt) { delete b; }
	vector<Button*> v;
	v.swap(bt);
}

//領域を設定
void Group::SetArea(int x, int y, int width, int height)
{
	Area.left = x;
	Area.top = y;
	Area.right = x + width;
	Area.bottom = y + height;
}

//ボタン追加
void Group::Add(Button* bt)
{
	this->bt.push_back(bt);	//ボタン追加
	ElementMax = this->bt.size();	//要素数設定
}

//描画
void Group::Draw()
{
	int NowDrawX = DrawX, NowDrawY = DrawY;		//現在の描画位置
	int row_cnt = 0;							//列数のカウント
	int line_cnt = 0;							//行数のカウント
	int now_page = 0;							//ページカウント

	for (auto b : bt)
	{
		if (row_cnt >= RowNum)		//列数が、描画できる範囲を超えたら
		{
			NowDrawX = DrawX + GAME_WIDTH * now_page;			//Xの描画位置を最初の位置へ
			NowDrawY += b->GetHeight() + Interval_Vertical;		//Yの描画位置を、画像の高さ＋間隔分下へずらす
			++line_cnt;											//カウントアップ
			row_cnt = 0;										//カウントリセット
		}

		if (line_cnt >= LineNum)	//行数が、描画できる範囲を超えたら
		{
			NowDrawX = DrawX + GAME_WIDTH;		//Xの位置を1画面分ずらした位置へ
			NowDrawY = DrawY;					//Yの位置を最初の位置へ
			++now_page;							//カウントアップ
			line_cnt = 0;						//カウントリセット
		}

		++row_cnt;	//カウントアップ

		b->Draw(NowDrawX,NowDrawY);	//描画

		NowDrawX += b->GetWidth() + Interval_Side;	//描画位置をずらす
	}
}

//クリックされた時の処理
void Group::Clik()
{
	for (int i = 0; i < bt.size(); ++i)	//ボタンの数
	{
		if (bt.at(i)->OnClick())	//ボタンを押されたとき
		{
			SelectNum = i;	//選択したボタンを保存
			return;			//処理終了
		}
	}
}

//選択したかどうか取得
/*
戻り値：bool：true 選択した： false 選択していない
*/
bool Group::GetIsSelect()
{
	return SelectNum != CHOISE_NONE;
}

//選択したボタンの要素番号を取得
/*
戻り値：int：選択したボタンの要素番号を取得
*/
int Group::GetSelctNum()
{
	return SelectNum;
}

//次のページへ行けるか確認
bool Group::CheckIsNextPage()
{
	//現在のページが、ページの最大数より前だったらtrue
	return NowPage < PageMax;

}

//前のページへ行けるか確認
bool Group::CheckIsPrevPage()
{
	//現在のページが、最初のページより後だったらtrue
	return NowPage > PAGE_START;
}

//次のページへ
void Group::NextPage()
{
	++NowPage;				//次のページへ
	DrawX -= GAME_WIDTH;	//描画位置を1ページ分ずらす
}

//前のページへ
void Group::PrevPage()
{
	--NowPage;				//前のページへ
	DrawX += GAME_WIDTH;	//描画位置をを1ページ分ずらす
}

//リセット
void Group::Reset()
{
	IsChoise = false;		//選択したか
	NowPage = PAGE_START;	//現在のページ
	SelectNum = -1;			//選択したボタン
	//描画位置リセット
	DrawX = S_DrawX;
	DrawY = S_DrawY;
}