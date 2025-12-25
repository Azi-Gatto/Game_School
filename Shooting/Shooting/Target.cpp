//Target.cpp
//的の基になるクラス

//################# ヘッダファイル読み込み ####################
#include "Target.hpp"

//################# クラス定義 ####################

vector<RECT> Target::use_rect;	//使用されている領域
vector<int> Target::ScoreTable;	//スコアテーブル

//コンストラクタ
Target::Target()
{
	//メンバー初期化
	DrawX = 0;				//描画X位置
	DrawY = 0;				//描画Y位置
	EventFlg = false;		//イベントフラグ
	img = new Image();		//画像
	time = new Time();		//時間
	effect = new Effect();	//エフェクト
	rect = { 0,0,0,0 };		//領域
	Element = use_rect.size();	//何番目の要素か
	use_rect.push_back(rect);		//使用済み領域追加

	if (ScoreTable.empty())	//テーブルが空なら
	{
		//的毎のスコアを任意に設定
		ScoreTable.push_back(100);	//おもちゃ01
		ScoreTable.push_back(150);	//おもちゃ02
		ScoreTable.push_back(200);	//おもちゃ03
		ScoreTable.push_back(-100);	//爆弾01
		ScoreTable.push_back(-150);	//爆弾02
		ScoreTable.push_back(-200);	//爆弾03
		ScoreTable.push_back(0);	//アイテム01
		ScoreTable.push_back(0);	//アイテム02
	}

}

//デストラクタ
Target::~Target()
{
	delete img;		//img破棄
	delete time;	//time破棄
	delete effect;	//effect破棄
}

//初期設定
void Target::SetInit()
{
	img->SetInit();		//画像初期設定
	do
	{
		CreateDrawPos();	//描画位置生成
	} while (RectOverRap());
	//領域の設定
	rect.left = DrawX;						//左X
	rect.top = DrawY;						//左Y
	rect.right = DrawX + img->GetWidth();	//右X
	rect.bottom = DrawY + img->GetHeight();	//右Y
	effect->SetInit();		//エフェクト
	time->StartCount();		//計測開始
}

//毎回行う処理
void Target::UpDate()
{

	if (!effect->GetIsNowEffect())	//エフェクト描画中じゃなければ
	{
		if (time->GetIsLimit())	//制限時間を超えたか
		{
			/*
			描画しているときは、描画を消す
			描画していない時は、次の描画までの時間が過ぎたときのため、再描画する
			*/
			img->SetIsDraw(!img->GetIsDraw());	//現在の描画状態の逆を設定

			do
			{
				CreateDrawPos();					//描画位置再生成
			} while (RectOverRap());

			time->SetLimit(GetRand(LIMIT_MAX - LIMIT_MIN) + LIMIT_MIN);	//制限時間設定
			time->StartCount();	//計測開始
		}

	}

}

//描画位置生成
void Target::CreateDrawPos()
{
	int max_x = GAME_WIDTH - img->GetWidth();	//描画位置Xの最大値を設定
	int max_y = GAME_HEIGHT - img->GetHeight();	//描画位置Yの最大値を設定
	DrawX = GetRand(max_x);	//描画X位置設定
	DrawY = GetRand(max_y);	//描画Y位置設定

	//領域の設定
	rect.left = DrawX;						//左X
	rect.top = DrawY;						//左Y
	rect.right = DrawX + img->GetWidth();	//右X
	rect.bottom = DrawY + img->GetHeight();	//右Y
	use_rect.at(Element) = rect;		//使用済みの領域を上書き
}

//自分の領域が、使用済みかどうか調べる
//戻り値: true 使用済み : false 未使用
bool Target::RectOverRap()
{
	int cnt = 0;	//カウント用
	for (auto r : use_rect)
	{
		if (Element != cnt++)	//自分の領域以外だったら
		{
			//領域が重なっているか判定
			if (rect.left < r.right &&
				rect.right > r.left &&
				rect.top < r.bottom &&
				rect.bottom > r.top)
			{
				return true;	//使用済み
			}

		}

	}
	return false;	//未使用
}

//描画
void Target::Draw()
{
	img->Draw(DrawX, DrawY);	//描画
}

//クリックされたか
bool Target::OnClick()
{
	if (!img->GetIsDraw())	//描画していない時は
		return false;		//クリックなし

	return Mouse::OnLeftClick(rect);
}

//イベントフラグ取得
bool Target::GetEventFlg()
{
	return EventFlg;
}

//イベントフラグ設定
void Target::SetEventFlg(bool flg)
{
	EventFlg = flg;
}
