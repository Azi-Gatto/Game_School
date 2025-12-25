//EFFECT.hpp
//エフェクトクラス

/*
エフェクト追加方法
・基本は、ANIMATIONクラスと同じ
・オブジェクト生成後は、Add処理を使用することで、エフェクトの追加をすることができる
*/

#pragma once

//###################### ヘッダファイル読み込み #########################
#include "DxLib.h"
#include <vector>
#include <string>
#include "FPS.hpp"
#include "main.hpp"

//###################### マクロ定義：ファイルパス、名前 ######################
#define MY_ANIME_DIR_ATKEFECT	R"(.\MY_ANIME\atack\)"			//攻撃エフェクトの画像ファイルの場所
#define MY_ANIME_DIR_MAGIC		R"(.\MY_ANIME\magic\)"			//魔法エフェクトの画像ファイルの場所
#define MY_ANIME_DIR_ENE_ATK	R"(.\MY_ANIME\enemy_atack\)"	//敵の攻撃エフェクトの画像のファイル場所
#define MY_ANIME_DIR_BOSS_ATK	R"(.\MY_ANIME\boss_atack\)"		//ボスの攻撃エフェクトの画像のファイル場所

#define MY_ANIME_NAME_ATKEFECT	R"(atack.png)"					//攻撃エフェクトの画像の名前
#define MY_ANIME_NAME_MAGIC		R"(magic.png)"					//魔法エフェクトの画像の名前
#define MY_ANIME_NAME_MAGIC2	R"(magic2.png)"					//魔法エフェクト2の画像の名前

#define MY_ANIME_NAME_ENE_ATK_TUME	R"(tume.png)"				//敵の攻撃（爪）のエフェクト画像の名前
#define MY_ANIME_NAME_ENE_ATK_KIBA	R"(kiba.png)"				//敵の攻撃（牙）のエフェクト画像の名前
#define MY_ANIME_NAME_ENE_ATK_TAIL_BIG	R"(tail_big.png)"		//敵の攻撃（尻尾大）のエフェクト画像の名前

#define MY_ANIME_NAME_BOSS_ATK_LASER	R"(boss_laser.png)"			//レーザーのエフェクト画像の名前
#define MY_ANIME_NAME_BOSS_ATK_TOGE		R"(boss_toge.png)"			//とげのエフェクト画像の名前

//###################### マクロ定義：エラーメッセージ ########################
#define EFFECT_ERROR_TTILE	"EFFECT_ERROR"						//エラータイトル
#define EFFECT_ERROR_MSG	"エフェクトが読み込めませんでした"	//エラーメッセージ

//###################### マクロ定義 #################################

//********************** サイズ ************************
//攻撃
#define ATK_WIDTH		120	//分割する幅の大きさ
#define ATK_HEIGHT		120	//分割する高さの大きさ
//魔法
#define MAGIC_WIDTH		880	//分割する幅の大きさ
#define MAGIC_HEIGHT	640	//分割する高さの大きさ
//敵の攻撃
#define ENE_ATK_TUME_WIDTH	240	//分割幅
#define ENE_ATK_TUME_HEIGHT	240	//分割高さ
#define ENE_ATK_KIBA_WIDTH	240	//分割幅
#define ENE_ATK_KIBA_HEIGHT	240	//分割高さ
#define ENE_ATK_TAIL_BIG_WIDTH 880	//分割幅
#define ENE_ATK_TAIL_BIG_HEIGHT	640	//分割高さ
//ボス
#define BOSS_ATK_LEASER_WIDTH	880	//分割幅
#define BOSS_ATK_LEASER_HEIGHT	640	//分割高さ
#define BOSS_ATK_TOGE_WIDTH		880	//分割幅
#define BOSS_ATK_TOGE_HEIGT		640	//分割高さ


//********************** 分割数 **************************
//攻撃
#define ATK_YOKO_CNT	9
#define ATK_TATE_CNT	1
//魔法
#define MAGIC_YOKO_CNT	1
#define MAGIC_TATE_CNT	12
#define MAGIC2_YOKO_CNT	5
#define MAGIC2_TATE_CNT	5
//敵の攻撃
#define ENE_ATK_TUME_YOKO_CNT 5	//横分割数
#define ENE_ATK_TUME_TATE_CNT 2	//縦分割数
#define ENE_ATK_KIBA_YOKO_CNT 5	//横分割数
#define ENE_ATK_KIBA_TATE_CNT 2	//縦分割数
#define ENE_ATK_TAIL_BIG_YOKO_CNT	5	//横分割数
#define ENE_ATK_TAIL_BIG_TATE_CNT	2	//縦分割数
//ボス
#define	BOSS_ATK_LEASER_YOKO_CNT	3	//横分割数
#define BOSS_ATK_LEASER_TATE_CNT	10	//縦分割数
#define BOSS_ATK_TOGE_YOKO_CNT		3	//横分割数
#define BOSS_ATK_TOGE_TATE_CNT		6	//縦分割数


//************************ 総分割数 **************************
//攻撃
#define ATK_ALL_CNT	ATK_YOKO_CNT * ATK_TATE_CNT
//魔法
#define MAGIC_ALL_CNT MAGIC_YOKO_CNT * MAGIC_TATE_CNT
#define MAGIC2_ALL_CNT	MAGIC2_YOKO_CNT * MAGIC2_TATE_CNT
//敵の攻撃
#define ENE_ATK_TUME_ALL_CNT 8	//総分割数
#define ENE_ATK_KIBA_ALL_CNT 8	//総分割数
#define ENE_ATK_TAIL_BIG_ALL_CNT ENE_ATK_TAIL_BIG_YOKO_CNT * ENE_ATK_TAIL_BIG_TATE_CNT	//総分割数
//ボス
#define BOSS_ATK_LEASER_ALL_CNT	BOSS_ATK_LEASER_YOKO_CNT * BOSS_ATK_LEASER_TATE_CNT	//総分割数
#define BOSS_ATK_TOGE_ALL_CNT	BOSS_ATK_TOGE_YOKO_CNT * BOSS_ATK_TOGE_TATE_CNT		//総分割数

//************************ 描画速度 ***************************
//攻撃
#define ATK_SPEED		 0.02
//魔法
#define MAGIC_SPEED		 0.02
//敵の攻撃
#define ENE_ATK_TUME_SPEED	0.05
#define ENE_ATK_KIBA_SPEED	0.05
#define ENE_ATK_TAIL_BIG_SPEED	0.05
//ボス
#define BOSS_ATK_LEASER_SPEED	0.02
#define BOSS_ATK_TOGE_SPEED		0.02


#define ATK_DRAW_X		375
#define ATK_DRAW_Y		290

#define MAGIC_EFFECT_KIND		2			//魔法エフェクトの種類
#define ATACK_EFFECT_KIND		1			//攻撃エフェクトの種類
#define ENE_ATK_EFFECT_KIND		3			//敵攻撃エフェクトの種類
#define BOSS_ATK_EFFECT_KIND	2			//ボスの攻撃エフェクトの種類

//###################### 列挙型 ##########################
enum MAGIC_EFFECT_TYPE
{
	MAGIC_1,			//魔法１
	MAGIC_2				//魔法２
};

enum ATACK_EFFECT_TYPE
{
	NOMAL_ATACK		//通常攻撃
};

enum ENEMY_ATACK_EFFECT_TYPE
{
	ENE_ATK_TUME,		//爪攻撃
	ENE_ATK_KIBA,		//牙攻撃
	ENE_ATK_TAIL_BIG	//尻尾（大）攻撃
};
enum BOSS_ATACK_EFFECT_TYPE
{
	BOSS_ATK_LEASER,		//レーザー
	BOSS_ATK_TOGE			//とげ　
};

//###################### クラス定義 ################################
class EFFECT
{
private:

	std::vector<std::vector<int>> Handle;							//ハンドル
	std::vector<int>::iterator Handle_itr;				//ハンドルのイテレータ
	
	std::vector<int> Width;				//幅
	std::vector<int> Height;			//高さ

	double NextChangeSpeed;			//アニメーションを変更する速さ(秒)
	int ChangeCnt;					//アニメーションするフレームのカウント
	int ChangeMaxCnt;				//アニメーションするフレームの最大値

	std::vector<bool> IsAnimeLoop;			//アニメーションはループする？
	std::vector<bool> IsAnimeStop;			//アニメーションはストップしたか？

	bool IsDrawEnd;				//描画終了したか

	bool IsLoad;				//読み込めたか？

public:

	EFFECT(const char *, const char *, int, int, int, int, int, double, bool,int);	//コンストラクタ	

	~EFFECT();					//デストラクタ

	int GetWidth(int);				//幅を取得
	int GetHeight(int);			//高さを取得

	bool GetIsLoad(void);			//読み込めた？

	bool GetIsAnimeStop(int);		//アニメーションはストップしたかを取得

	bool GetIsDrawEnd();		//描画終了したか取得

	void SetIsDrawEnd(bool);	//描画終了したか設定

	void ResetIsAnime(int);		//アニメーションがストップしたかをリセット

	void Draw(int, int,int);			//描画
	void DrawNormal(int, int, int);			//描画(フェードアウトなし)

	bool Add(const char *, const char *, int, int, int, int, int, double, bool, int);	//エフェクト追加

	void SetSize();				//サイズ設定

};
