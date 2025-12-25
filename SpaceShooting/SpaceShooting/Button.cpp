//Button.cpp
//ボタンのクラス

//############### ヘッダファイル読み込み ###################
#include "Button.hpp"

//############### クラス定義 ###############

Music* Button::se;			//効果音

//コンストラクタ
Button::Button(const char *text)
{
	this->text = text;	//文字設定
	rect = { 0 };	//領域初期化
	if (se == NULL)	//効果音が空なら
	{
		se = new Music(MUSIC_DIR_SE, SE_NAME_KETTEI);	//効果音追加
	}
}

//コンストラクタ
Button::Button(Image* img)
{
	this->img = img;
	rect = { 0 };	//領域初期化
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
	//領域設定
	rect.left = x;						//左上X
	rect.top = y;						//左上Y
	int width = 0, height = 0;	//横幅、高さ
	if (img == NULL)	//画像が設定されていない場合
	{
		//テキストのサイズを取得
		width = GetDrawStringWidth(text.c_str(), strlen(text.c_str()));	//横幅取得
		height = GetFontSize();	//高さ取得
	}
	else		//画像が設定されている場合
	{
		//画像のサイズを取得
		img->SetInit();				//画像初期設定
		width = img->GetWidth();	//画像の横幅取得
		height = img->GetHeight();	//画像の高さ取得
	}
	rect.right = x + width;		//右下X
	rect.bottom = y + height;	//右下Y
	se->SetInit(DX_PLAYTYPE_BACK, 60);	//効果音

}

//更新処理
void Button::UpDate()
{
	//マウスがボタンの領域の中にあるか
	if (Mouse::HoverRect(rect))	//領域内の時
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, RECT_TOUKA_VALUE * TOUKA_MAX_VALUE);	//透過させる
		DrawBox(rect.left, rect.top, rect.right, rect.bottom, COLOR_GRAY, TRUE);	//薄い四角形を描画
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);									//透過をやめる
	}
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
	if (img == NULL)	//画像が設定されていない場合
	{
		DrawString(rect.left, rect.top, text.c_str(), COLOR_WHITE);	//文字描画
	}
	else //画像が設定されている場合
	{
		img->Draw(rect.left, rect.top);	//画像描画
	}
}
