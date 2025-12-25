//CHARACTOR.cpp
//キャラクタークラス

//################# ヘッダファイル読み込み #####################
#include "CHARACTOR.hpp"

//################ クラス定義 ########################
//コンストラクタ
CHARACTOR::CHARACTOR()
{
	
	//メンバー変数初期化
	this->IsArive = false;	//死んでいる
	this->IsLoad = false;	//読み込めていない

	return;
}

//デストラクタ
CHARACTOR::~CHARACTOR()
{
	delete this->image;		//image削除

	return;
}

//生きているか設定
void CHARACTOR::SetIsArive(bool Isarive)
{
	this->IsArive = Isarive;
	return;
}

//画像を設定
//引　数：const char *：画像のディレクトリ
//引　数：const char *：画像の名前
void CHARACTOR::SetImage(const char *dir, const char *name)
{
	this->image = new IMAGE(dir, name);
	this->IsLoad = this->image->GetIsLoad();	//読み込めたか設定

	return;

}

//画像を追加
//引　数：const char *：画像のディレクトリ
//引　数：const char *：画像の名前
bool CHARACTOR::AddImage(const char *dir, const char *name)
{
	return this->image->AddImage(dir, name);	
}

//画像を変更する
//引数：int：変更する画像の番号
void CHARACTOR::ChengeImage(int kind)
{
	this->image->ChengeImage(kind);
	return;
}

//横幅を取得
int CHARACTOR::GetWidth()
{
	return this->image->GetWidth();
}

//高さを取得
int CHARACTOR::GetHeight()
{
	return this->image->GetHeight();
}

//画像の位置を設定する
void CHARACTOR::SetImagePos(int x, int y)
{

	this->Draw_X = x;
	this->Draw_Y = y;

}

//生きているか取得
bool CHARACTOR::GetIsArive()
{
	return this->IsArive;
}

//読み込めたか取得
bool CHARACTOR::GetIsLoad()
{
	return this->IsLoad;
}

//操作
void CHARACTOR::Operation(KEYDOWN *keydown)
{
	return;
}

//初期化設定
void CHARACTOR::SetInit()
{

	this->image->SetSize();		//画像サイズ設定

	this->IsArive = true;		//生きている

	return;

}

//描画
void CHARACTOR::Draw()
{
	if (this->IsArive)	//生きていれば
	{
		this->image->Draw(this->Draw_X, this->Draw_Y);	//画像描画
	}
}

//フェードアウトするか設定
void CHARACTOR::SetFade(bool isfade)
{
	this->image ->SetIsFade(isfade);
	return;
}

//描画するか設定
void CHARACTOR::SetIsDraw(bool isdraw)
{
	this->image->SetIsDraw(isdraw);
	return;
}

//フェードエフェクトが終了したか取得
bool CHARACTOR::GetFadeEnd()
{
	return this->image->GetFadeEnd();
}