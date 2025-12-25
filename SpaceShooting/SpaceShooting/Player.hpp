//Player.hpp
//プレイヤーを管理するクラス

#pragma once

//############# ヘッダファイル読み込み ###########
#include "Global.hpp"
#include "Image.hpp"
#include "Bullet.hpp"

//############# マクロ定義 ############

//############# クラス定義 ############
class Player
{
private:

	vector<Bullet*> bullet;	//弾
	Image* img;		//画像
	RECT collision;	//当たり判定

	int Hp;			//HP

	int SpawnX;		//弾発射地点X
	int SpawnY;		//弾発射地点Y

	void Move();	//移動

public:

	Player(Image*);			//コンストラクタ
	~Player();				//デストラクタ

	void UpDate();		//毎回行う処理
	void Draw();		//描画
	void SetInit();		//初期設定
	void Init();		//初期化
	RECT GetCol();			//当たり判定取得
	RECT GetBulletCol(int);	//弾の当たり判定取得
	int GetBulleMax();		//現在の玉の数を取得
	void HitBullet(int);	//敵に弾が当たった

};
