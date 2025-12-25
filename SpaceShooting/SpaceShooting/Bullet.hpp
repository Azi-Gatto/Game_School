//Bullet.hpp
//弾を管理するクラス

#pragma once

//################# ヘッダファイル読み込み #################
#include "Global.hpp"
#include "Animation.hpp"

//################## マクロ定義 ####################
#define BULLET_SPEED 5	//弾の速度

//################## クラス定義 ####################
class Bullet
{
private:

	Animation* anim;		//弾のアニメーション
	RECT collision;			//当たり判定
	int Speed;				//速さ
	bool IsDraw;			//描画しているか
	bool IsMove;			//移動するか
	static int ElementCnt;	//要素番号カウント用

public:

	Bullet();			//コンストラクタ
	~Bullet();			//デストラクタ

	void SetInit(int,int);		//初期設定

	void Draw();				//描画
	void Move();				//移動
	void Shot();				//撃つ
	bool InScreen();			//画面内か
	RECT GetCol();				//当たり判定取得
	static int GetElementMax();	//要素番号取得
	void SetIsMove(bool);		//移動するか

};
