//CHARACTOR.hpp
//キャラクタークラス

#pragma once

//###################### ヘッダファイル読み込み ###################
#include "DxLib.h"
#include "main.hpp"
#include "IMAGE.hpp"
#include "KEYDOWN.hpp"
#include "COLLISION.hpp"
#include "SIKAKU.hpp"


//###################### マクロ定義 #######################

//###################### クラス定義 #######################
class CHARACTOR
{
private:
	IMAGE *image;				//画像
	COLLISION *collision;		//当たり判定の領域
	SIKAKU *sikaku_draw;		//キャラの描画する領域

	int Speed;					//移動速度

	bool IsArive;				//生きているか
	bool IsKeyOperation;		//キーボードで操作できるか
	bool IsDraw;				//描画できるか

public:

	CHARACTOR();				//コンストラクタ
	~CHARACTOR();				//デストラクタ

	void MoveUp();				//上へ移動
	void MoveDown();			//下へ移動
	void MoveLeft();			//左へ移動
	void MoveRight();			//右へ移動

	void SetIsArive(bool);		//生きているかを設定
	void SetIsDraw(bool);		//描画してよいかを設定
	void SetSpeed(int);			//移動速度を設定
	void SetKeyOperation(bool); //キーボードで操作できるか設定
	bool SetImage(const char*, const char*);//画像設定

	void SetImagePos(int, int);		//画像の位置を設定する

	int  GetWidth();			//横幅取得
	int GetHeight();			//高さ取得
	bool GetIsArive();			//生きているか取得
	bool GetIsDraw();			//描画できるか取得
	int GetSpeed();				//移動速度を取得
	bool GetKeyOperation();		//キーボードで操作できるか取得
	COLLISION * GetCollision();	//当たり判定を取得

	void Operation(KEYDOWN *);	//操作

	void Draw();				//描画

	bool SetInit();				//初期設定

};

