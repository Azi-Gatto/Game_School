//Button.cpp
//ボタンのクラス

//############### ヘッダファイル読み込み ###################
#include "Button.hpp"

//############### クラス定義 ###############

int Button::ElementCnt = 0;	//要素数
Music* Button::se;			//効果音

//コンストラクタ
Button::Button(Image* img)
{
	this->img = img;
	rect = { 0 };	//領域初期化
	Element = ElementCnt++;	//要素番号設定
	if (se == NULL)	//効果音が空なら
	{
		se = new Music(MUSIC_DIR_SE, SE_NAME_KETTEI);	//効果音追加
	}
}

//デストラクタ
Button::~Button()
{
	delete img;	//img破棄
	delete se;	//se破棄
}

//初期設定
void Button::SetInit(int x,int y)
{
	img->SetInit();	//画像初期設定
	SetRect(x, y);	//領域設定
	se->SetInit(DX_PLAYTYPE_BACK, VOL_DEF);	//効果音

}

//初期設定
void Button::SetInit()
{
	img->SetInit();	//画像初期設定
	se->SetInit(DX_PLAYTYPE_BACK, VOL_DEF);	//効果音
}

//ボタンをクリックされたか
bool Button::OnClick()
{
	se->Reset();	//再生状態リセット
	bool click = Mouse::OnLeftClick(rect);
	if (click)	//クリックされたら
		se->PlayOne();	//効果音再生

	return click;
}

//描画
void Button::Draw()
{
	//マウスがボタンの領域の中にあるか
	if (Mouse::HoverRect(rect))	//領域内の時
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, RECT_TOUKA_VALUE * TOUKA_MAX_VALUE);	//透過させる
		DrawBox(rect.left, rect.top, rect.right, rect.bottom, COLOR_GRAY, TRUE);	//薄い四角形を描画
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);									//透過をやめる
	}
	img->Draw(rect.left, rect.top);
}

//描画（位置指定）
void Button::Draw(int x, int y)
{
	SetRect(x, y);	//領域再設定
	//マウスがボタンの領域の中にあるか
	if (Mouse::HoverRect(rect))	//領域内の時
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, RECT_TOUKA_VALUE * TOUKA_MAX_VALUE);	//透過させる
		DrawBox(x, y, x + img->GetWidth(), y + img->GetHeight(), COLOR_GRAY, TRUE);	//薄い四角形を描画
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);									//透過をやめる
	}
	img->Draw(x,y);
}

//要素番号取得
int Button::GetElement()
{
	return Element;
}

//横幅取得
int Button::GetWidth()
{
	return img->GetWidth();
}

//高さ取得
int Button::GetHeight()
{
	return img->GetHeight();
}

//領域を設定
void Button::SetRect(int x, int y)
{
	rect.left = x;
	rect.top = y;
	rect.right = x + img->GetWidth();
	rect.bottom = y + img->GetHeight();
}
