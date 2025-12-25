//Enemy.hpp
//敵を管理するクラス

#pragma once

//############### ヘッダファイル読み込み ####################
#include "Charactor.hpp"
#include "Effect.hpp"

//############### マクロ定義 ####################
#define IMG_DIR_ENEMY	R"(.\Image\Enemy)"			//敵の画像のディレクトリ

#define IMG_NAME_ENEMY01	R"(\enemy.png)"		//敵(1体目)の画像の名前
#define IMG_NAME_ENEMY02	R"(\enemy2.png)"	//敵(2体目)の画像の名前
#define IMG_NAME_ENEMY03	R"(\enemy3.png)"	//敵(3体目)の画像の名前
#define IMG_NAME_ENEMY_HP	R"(\enemy_hp.png)"	//敵のHPの画像の名前

#define ENEMY_MAX		3			//敵の最大数

//############### クラス定義 ####################
class Enemy :public Charactor		//CHARACTORクラスを継承
{
private:

	Image* img;				//画像
	Effect* damege;			//ダメージエフェクト
	RECT rect;				//描画範囲
	bool dmgFlg;			//ダメージフラグ

	static bool AllKill;	//全ての敵を倒したか
	static int NowEnemyNum;	//現在何体目の敵か

public:

	Enemy(const char* ,const char*);	//コンストラクタ
	~Enemy();							//デストラクタ

	bool SetInit() override;			//初期設定
	void Init() override;				//初期化

	static void NextEnemy();			//次の敵へ
	static int GetNowEnemyNum();		//現在何体目の敵か取得

	void Draw() override;				//敵キャラ描画
	bool GetFadeEnd();					//フェードアウト終了したか
	void SetDamegeFlg(bool);			//ダメージフラグ設定
	bool GetIsEffectEnd();				//エフェクト終了したか
	static bool GetAllEnemyKilled();	//すべての敵を倒したか

};
