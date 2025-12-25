//Enemy.hpp
//敵キャラを管理するクラス

#pragma once

//############ ヘッダファイル読み込み ###############
#include "Global.hpp"
#include "Image.hpp"
#include "Player.hpp"
#include "Effect.hpp"

//############ マクロ定義 ################
#define ENEMY_SPD_MAX	3	//敵の移動速度MAX
#define ENEMY_SPD_MIN	1	//敵の移動速度MIN
#define SPAWN_LEFT	150		//敵の発生左端
#define SPAWN_RIGHT	700		//敵の発生右端
#define SPAWN_HEIGHT 100	//敵の発生高さ幅


//############ クラス定義 ################
class Enemy
{

private:

	Effect* explosion;	//爆発エフェクト
	Music* exp_se;		//爆発音
	Image* img;		//画像
	RECT collision;	//当たり判定

	int Hp;			//HP
	int Speed;		//速さ

	bool Hit;		//当たった
	bool IsLoad;	//読み込めた
	bool IsMove;	//移動しているか

	static int DestroyCnt;	//倒された数
	static bool End;		//終了フラグ

	bool OnCollision(RECT);	//当たり判定の処理
	void Spawn();			//生成
	bool InScreen();		//画面内か

public:

	Enemy(Image*);			//コンストラクタ
	~Enemy();				//デストラクタ

	void UpDate(Player*);	//毎回行う処理
	void SetInit();			//初期設定
	void Init();			//初期化
	void Draw();			//描画
	bool GetIsLoad();		//読み込めたか取得
	void Move();			//移動
	static bool GetIsEnd();	//終了か
	static int GetDestroyNum();	//倒した数を取得

};
