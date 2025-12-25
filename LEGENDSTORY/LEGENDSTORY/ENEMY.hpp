//ENEMY.hpp
//敵の情報を管理するクラス

/*
追加方法
・画像ファイルの名前をマクロ定義に追加する
・マクロ定義されている、敵の種類数を増やす
・列挙型、ENEMY_TYPEの要素を追加する
・"main.cpp"内のデータ読み込み処理で、追加した敵の生成処理を追加する
・敵のステータス情報などは、csvファイルに書き込み、DATAクラスを使用して、読み込む
*/

#pragma once

//############### ヘッダファイル読み込み ###################
#include "DxLib.h"
#include "CHARACTOR.hpp"
#include "ANIMATION.hpp"
#include "main.hpp"
#include "EFFECT.hpp"
#include <vector>

//############### マクロ定義：ファイルパス、名前 ################
#define ENEMY_DIR			R"(.\MY_IMG\ENEMY\)"	//敵の画像のファイル

#define ENEMY_NAME_SLIME	R"(sraim.png)"			//スライムの画像の名前
#define ENEMY_NAME_BAT		R"(bat.png)"			//こうもりの画像の名前
#define ENEMY_NAME_GOBURIN	R"(goburin.png)"		//ゴブリンの画像の名前

#define ENEMY_NAME_MATANGO	R"(kinoko.png)"			//マタンゴの画像の名前
#define ENEMY_NAME_SEED		R"(seed.png)"			//悪魔の種の画像の名前
#define ENEMY_NAME_TREANT	R"(treant.png)"			//トレントの画像の名前

#define ENEMY_NAME_YADOKARI	R"(yadokari.png)"		//ヤドカリの画像の名前
#define ENEMY_NAME_SCORPION	R"(scorpion.png)"		//サソリの画像の名前
#define ENEMY_NAME_OCTPUS	R"(octpus.png)"			//タコの画像の名前

#define ENEMY_NAME_COBRA	R"(cobra.png)"			//コブラの画像の名前
#define ENEMY_NAME_PUMPKIN	R"(kabocha.png)"		//パンプキンの画像の名前
#define ENEMY_NAME_PAPILLON	R"(papillon.png)"		//パピオンの画像の名前

#define ENEMY_NAME_HARPY	R"(harpy.png)"			//ハーピーの画像の名前
#define ENEMY_NAME_FLOWER	R"(flower.png)"			//デスフラワーの画像の名前
#define ENEMY_NAME_MANTIS	R"(mantis.png)"			//マンティスの画像の名前

#define ENEMY_NAME_CRYSTAL	R"(crystal.png)"		//クリスタルの画像の名前
#define ENEMY_NAME_ICICLE	R"(icicle.png)"			//アイシクルの画像の名前
#define ENEMY_NAME_SNOWMAN	R"(snowman.png)"		//スノーマンの画像の名前

#define ENEMY_NAME_FARAO	R"(farao.png)"			//ファラオの画像の名前
#define ENEMY_NAME_AKUMA	R"(akuma.png)"			//悪魔の画像の名前
#define ENEMY_NAME_BONEBEAST R"(bone-b.png)"		//ボーンビーストの画像の名前

#define ENEMY_NAME_IFRIT	R"(ifrit.png)"			//イフリートの画像の名前
#define ENEMY_NAME_GARGOYLE R"(gargoyle.png)"		//ガーゴイルの画像の名前
#define ENEMY_NAME_PROMINENCE	R"(prominence.png)"	//プロミネンスの画像の名前

#define ENEMY_NAME_BOSS		R"(maou.png)"			//魔王の画像の名前
#define ENEMY_NAME_BOSS_MAP	R"(maou_mapimage.png)"	//マップに描画する魔王の画像の名前

//############## マクロ定義：エラーメッセージ ###################

//############## マクロ定義 ###################
#define ENEMY_KIND 25			//敵の種類

#define BOSS_MAP_X	418			//ボスのマップでの描画位置X
#define BOSS_MAP_Y	10			//ボスのマップでの描画位置Y

#define ENEMY_ENCOUNT_TYPE_NONE	-1	//敵と遭遇していないとき

#define ENEMY_NONE	-1			//初期値

#define ENEMY_DROP_KIND 3		//ドロップする物の種類
#define DROP_JUDGE_NUM	100		//ドロップした物の種類を判別するのに使用する

//############## 列挙型 ########################
enum ENEMY_TYPE
{
	ENE_SLIME,				//スライム
	ENE_BAT,				//こうもり
	ENE_GOBURIN,			//ゴブリン
	ENE_MATANGO,			//マタンゴ
	ENE_SEED,				//悪魔の種
	ENE_TREANT,				//トレント
	ENE_YADOKARI,			//ヤドカリ
	ENE_SCORPION,			//サソリ
	ENE_OCTPUS,				//タコ
	ENE_COBRA,				//コブラ
	ENE_PUMPKIN,			//パンプキン
	ENE_PAPILLON,			//パピオン
	ENE_HARPY,				//ハーピー
	ENE_FLOWER,				//デスフラワー
	ENE_MANTIS,				//マンティス
	ENE_CRYSTAL,			//クリスタル
	ENE_ICICLE,				//アイシクル
	ENE_SNOWMAN,			//スノーマン
	ENE_FARAO,				//ファラオ
	ENE_AKUMA,				//悪魔
	ENE_BONEBEAST,			//ボーンビースト
	ENE_IFRIT,				//イフリート
	ENE_GARGOYLE,			//ガーゴイル
	ENE_PROMINENCE,			//プロミネンス
	ENE_BOSS				//魔王
};

enum DROP_TYPE
{
	DROP_TYPE_ITEM,		//アイテム
	DROP_TYPE_WEAPON,	//武器
	DROP_TYPE_ARMOR		//防具
};

//############## クラス定義 #####################
class ENEMY :public CHARACTOR		//キャラクタークラスを継承
{
private:

	std::string Name;	//名前

	int MaxHP;	//最大HP
	int HP;		//体力
	int ATK;	//攻撃力
	int DEF;	//防御力
	int SPD;	//はやさ
	
	int EXP;	//経験値

	int RecvDamege;	//受けるダメージ

	int EmergenceMap;	//出現するMAPのNo
	int EncounteRate;	//遭遇率

	std::vector<int> Skil;	//スキル
	int ChoiseSkil;			//使用するスキル

	int ItemCode;	//アイテムコード
	int WeaponCode;	//武器コード
	int ArmorCode;	//防具コード

	bool IsLoad;	//読み込めたか

public:

	ENEMY(const char *,const char *);			//コンストラクタ

	~ENEMY();			//デストラクタ

	void SetName(const char *);	//名前設定
	void SetMaxHP(int);		//最大体力設定
	void SetHP(int);		//体力設定
	void SetATK(int);		//攻撃力設定
	void SetDEF(int);		//防御力設定
	void SetSPD(int);		//速度設定
	void SetSkil(int);		//スキル設定
	void SetEXP(int);		//経験値設定
	void SetRecvDamege(int);//受けるダメージを設定

	void SetEmergenceMap(int);	//出現MAPNoの設定
	void SetEncounteRate(int);	//遭遇率設定

	void SetItemCode(int);		//アイテムコード設定
	void SetWeaponCode(int);	//武器コード設定
	void SetArmorCode(int);		//防具コード設定

	void StateSetInit();	//敵ステータス初期化

	const char * GetName();			//名前取得
	int GetHP();			//体力取得
	int GetATK();			//攻撃力取得
	int GetDEF();			//防御力取得
	int GetSPD();			//速度取得
	int GetChoiseSkil();	//使用するスキルの種類を取得
	int GetEXP();			//経験値取得
	int GetRecvDamege();	//受けるダメージ取得
	
	int GetEmergenceMap();	//出現MAPNoの所得
	int GetEncounteRate();	//遭遇率の取得

	bool GetIsLoad();		//読み込めたかを取得

	void ActDecision();		//行動決定処理
	void DamegeSend();		//ダメージを与える
	int Drop();				//ドロップ処理

};
