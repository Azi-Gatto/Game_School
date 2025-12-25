//CHARACTOR.cpp
//キャラクタークラス

//################# ヘッダファイル読み込み #####################
#include "CHARACTOR.hpp"

//################ クラス定義 ########################
//コンストラクタ
CHARACTOR::CHARACTOR()
{
	return;
}

//デストラクタ
CHARACTOR::~CHARACTOR()
{
	delete this->collision;	//collision削除
	delete this->image;		//image削除
	delete this->sikaku_draw;	//sikaku_draw削除

	return;
}

//上へ移動
void CHARACTOR::MoveUp()
{
	if (this->sikaku_draw->Top - this->Speed >= GAME_TOP)
	{
		this->sikaku_draw->Top -= this->Speed;	//当たり判定と、描画位置を上へ移動
	}

	return;
}

//下へ移動
void CHARACTOR::MoveDown()
{
	if (this->sikaku_draw->Bottom + this->Speed <= GAME_HEIGHT)
	{
		this->sikaku_draw->Top += this->Speed;	//下へ移動
	}
	return;
}

//左へ移動
void CHARACTOR::MoveLeft()
{
	if (this->sikaku_draw->Left - this->Speed >= GAME_LEFT)
	{
		this->sikaku_draw->Left -= this->Speed;	//左へ移動
	}
	return;
}

//右へ移動
void CHARACTOR::MoveRight()
{
	if (this->sikaku_draw->Right + this->Speed <= GAME_WIDTH)
	{
		this->sikaku_draw->Left += this->Speed;	//右へ移動
	}
	return;
}

//生きているか設定
void CHARACTOR::SetIsArive(bool Isarive)
{
	this->IsArive = Isarive;
	return;
}

//描画できるか設定
void CHARACTOR::SetIsDraw(bool Isdraw)
{
	this->IsDraw = IsDraw;
	return;
}

//移動速度を設定
void CHARACTOR::SetSpeed(int speed)
{
	this->Speed = speed;
	return;
}

//キーボードで操作できるか設定
void CHARACTOR::SetKeyOperation(bool Iskeyoperation)
{
	this->IsKeyOperation = IsKeyOperation;
	return;
}

//画像を設定
bool CHARACTOR::SetImage(const char *dir, const char *name)
{
	this->image = new IMAGE(dir, name);
	if (this->image->GetIsLoad() == false) { return false; }	//読み込み失敗

	return true;

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
	this->collision->Left = x;	//X座標
	this->collision->Top = y;	//Y座標

	this->sikaku_draw->Left = x;
	this->sikaku_draw->Top = y;

	//描画猟奇
	this->sikaku_draw->SetValue(
		this->sikaku_draw->Left,
		this->sikaku_draw->Top,
		this->sikaku_draw->Width,
		this->sikaku_draw->Height
	);

	//領域再設定
	this->collision->SetValue(
		this->collision->Left,
		this->collision->Top,
		this->collision->Width,
		this->collision->Height
	);
}

//生きているか取得
bool CHARACTOR::GetIsArive()
{
	return this->IsArive;
}

//描画できるか取得
bool CHARACTOR::GetIsDraw()
{
	return this->IsDraw;
}

//移動速度を取得
int CHARACTOR::GetSpeed()
{
	return this->Speed;
}

//キーボード操作できるか取得
bool CHARACTOR::GetKeyOperation()
{
	return this->IsKeyOperation;
}

//当たり判定を取得
COLLISION * CHARACTOR::GetCollision()
{
	return this->collision;
}

//操作
void CHARACTOR::Operation(KEYDOWN *keydown)
{

	if (keydown->IsKeyDown(KEY_INPUT_W))		//Wキーを押しているとき
	{
		this->MoveUp();							//上へ移動
	}
	else if (keydown->IsKeyDown(KEY_INPUT_S))	//Sキーを押しているとき
	{
		this->MoveDown();						//下へ移動
	}
	else if (keydown->IsKeyDown(KEY_INPUT_A))	//Aキーを押しているとき
	{
		this->MoveLeft();						//左へ移動
	}
	else if (keydown->IsKeyDown(KEY_INPUT_D))	//Dキーを押しているとき
	{
		this->MoveRight();						//右へ移動
	}

	//描画領域再設定
	this->sikaku_draw->SetValue(
		this->sikaku_draw->Left,
		this->sikaku_draw->Top,
		this->sikaku_draw->Width,
		this->sikaku_draw->Height);

	//領域再設定
	this->collision->SetValue(
		this->collision->Left,
		this->collision->Top,
		this->collision->Width,
		this->collision->Height);

	return;
	
}

//初期化設定
bool CHARACTOR::SetInit()
{

	this->image->SetSize();		//画像サイズ設定

	this->collision = new COLLISION();		//当たり判定の領域を作成
	this->collision->SetValue(GAME_LEFT, GAME_TOP, this->image->GetWidth(), this->image->GetHeight());	//当たり判定の領域を設定

	this->sikaku_draw = new SIKAKU();		//描画領域を作成
	this->sikaku_draw->SetValue(GAME_LEFT, GAME_TOP, this->image->GetWidth(), this->image->GetHeight());	//当たり判定の領域を設定

	this->IsArive = true;	//生きている
	this->IsDraw = true;	//描画してよい
	this->IsKeyOperation = true;	//キーボード操作できる

	this->SetImagePos(GAME_WIDTH / 2 - this->GetWidth() / 2, GAME_HEIGHT / 2 - this->GetHeight() / 2);	//位置調整(画面中央)

	return true;

}

//描画
void CHARACTOR::Draw()
{
	if (this->IsArive)	//生きていれば
	{
		if (this->IsDraw)	//描画できれば
		{
			this->image->Draw(this->sikaku_draw->Left, this->sikaku_draw->Top);	//画像描画
		}
	}
}
