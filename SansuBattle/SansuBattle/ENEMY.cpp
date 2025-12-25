//Enemy.cpp
//敵を管理するクラス

//############### ヘッダファイル読み込み ##################
#include "Enemy.hpp"

//############### クラス定義 #####################

//インスタンスを生成
int Enemy::NowEnemyNum = 0;
bool Enemy::AllKill = false;	//全ての敵を倒したか

//コンストラクタ
//引　数：const char *：画像のディレクトリ
//引　数：const char *：画像の名前
Enemy::Enemy(const char* dir, const char* name)
{
	//画像生成
	img = new Image(dir, name);	//画像生成
	hp_img->Load(IMG_DIR_ENEMY, IMG_NAME_ENEMY_HP);	//HP画像生成

	//ダメージエフェクト生成
	damege = new Effect(new Animation(ANIM_DAMEGE, ANIM_DAMEGE_SPEED, false), new Music(MUSIC_DIR_EFFECT, SE_NAME_EF_DAMEGE));
	dmgFlg = false;		//ダメージフラグ

	HP_X = GAME_LEFT;	//HP描画X位置
	HP_Y = GAME_TOP;	//HP描画Y位置

	rect = { 0 };	//描画範囲

}

//デストラクタ
Enemy::~Enemy()
{
	delete img;		//img破棄
	delete damege;	//damege破棄
}

//初期設定
bool Enemy::SetInit()
{
	if (!hp_img->GetIsLoad()) { return false; }	//読み込み失敗
	if (!img->GetIsLoad()) { return false; }	//読み込み失敗
	if (!damege->GetIsLoad()) { return false; }	//読み込み失敗
	img->SetInit();		//敵キャラ画像初期設定
	hp_img->SetInit();	//HP
	damege->SetInit();	//ダメージエフェクト

	//描画範囲設定
	rect.left = GAME_WIDTH / 2 - img->GetWidth() / 2;
	rect.top = GAME_HEIGHT / 2 - img->GetHeight() / 2;
	rect.right = rect.left + img->GetWidth();
	rect.bottom = rect.top + img->GetHeight();
}

//初期化
void Enemy::Init()
{
	NowEnemyNum = 0;	//現在の敵の数を初期化
	HP = HP_INIT_VALUE;	//HP初期化
	IsArive = true;		//生きている
	img->SetIsFade(false);	//フェードアウトしない。
	AllKill = false;	//全ての敵を倒したか

}

//次の敵へ
void Enemy::NextEnemy()
{
	if (NowEnemyNum < ENEMY_MAX - 1)	//現在の敵が、敵の最大数より少なければ
	{
		++NowEnemyNum;				//次の敵へ
	}
	else	//敵の数が最大になったら
	{
		AllKill = true;	//全ての敵を倒した
	}
}

//現在何体目の敵か取得
int Enemy::GetNowEnemyNum()
{
	return NowEnemyNum;
}

//描画
void Enemy::Draw()
{

	//HP描画
	for (int i = 0; i < HP; ++i)
	{
		if (reverse)	//反転描画するとき
		{
			hp_img->Draw(HP_X - i * hp_img->GetWidth(), HP_Y);	//反転描画
		}
		else	//通常描画のとき
		{
			hp_img->Draw(HP_X + i * hp_img->GetWidth(), HP_Y);	//HP描画
		}
	}

	//敵描画
	if (!KillFlg)	//キルフラグが立っていなければ
	{
		img->DrawCenter();		//中央に描画
		if (dmgFlg)	//ダメージを受けたとき
		{
			damege->DrawCenter(rect);	//ダメージエフェクト描画
		}
	}
	if (KillFlg)	//キルフラグが立っていれば
	{
		img->SetIsFade(true);	//フェードアウト開始
		img->DrawCenter();		//中央に描画

		//if (GetFadeEnd())		//フェードアウト終了したら
		//{
		//	if (NowEnemyNum == ENEMY_MAX - 1)	//最後の敵を倒したら
		//	{
		//		AllKill = true;	//全ての敵を倒した
		//	}
		//	//NextEnemy();		//次の敵へ
		//}
	}
}

//フェードアウト終了したか取得
bool Enemy::GetFadeEnd()
{
	return img->GetFadeEnd();
}

//ダメージフラグ設定
void Enemy::SetDamegeFlg(bool dmg)
{
	dmgFlg = dmg;
}

//エフェクト終了したか
bool Enemy::GetIsEffectEnd()
{
	if (damege->GetIsEffectEnd())	//エフェクト描画が終了したら
	{
		damege->Reset();			//エフェクトリセット
		dmgFlg = false;				//ダメージフラグリセット
		return true;				//エフェクト終了
	}
	else	//終了していなければ
	{
		return false;	//終了していない
	}
}

//すべての敵を倒したか取得
bool Enemy::GetAllEnemyKilled()
{
	return AllKill;
}
