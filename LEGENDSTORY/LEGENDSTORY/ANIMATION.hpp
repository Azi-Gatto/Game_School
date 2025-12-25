/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
/* ANIMATION.hpp     																			　 */
/* アニメーションクラス 																		　 */

/*
追加方法
・MY_ANIMEフォルダ内に、アニメーションの種類のフォルダを作る
　例：攻撃のアニメーション→atackフォルダ
  例：敵の攻撃アニメーション→enemy_atackフォルダ、等
・作成したフォルダの中に、アニメーションの画像を追加する
・"ANIMATION.hpp"内に、以下のマクロ定義を追加する
　・アニメーションの種類のフォルダのディレクトリ
 　例：MY_ANIME_DIR_PLAYER、等
  ・アニメーションの画像名
  ・分割する幅
  ・分割する高さ
  ・横、縦、合計の分割数
  ・アニメーションさせる速度
 ・追加したマクロ定義をクラスを作成するときに引数として渡す。（引数の順番は、"ANIMATION.cpp"のコンストラクタの定義部に記載）
*/

#pragma once

//########## ヘッダーファイル読み込み ##########
#include "DxLib.h"
#include <string>
#include <vector>

#include "FPS.hpp"

//########## マクロ定義：画像のファイルパスと名前 ##########
#define MY_ANIME_DIR_PLAYER		R"(.\MY_ANIME\walk\)"			//プレイヤーの画像ファイルの場所
#define TXT_POSE_DIR			R"(.\MY_ANIME\Ui\)"				//UIの画像ファイルの場所

#define MY_ANIME_NAME_PLAYER	R"(player_work.png)"			//プレイヤーの画像の名前
#define TXT_POSE_NAME			R"(txtpose.png)"				//テキストポーズの画像の名前

#define PLAYER_WIDTH	24	//分割する幅の大きさ
#define PLAYER_HEIGHT	24	//分割する高さの大きさ

#define TXT_POSE_WIDTH	30	//分割高さ
#define TXT_POSE_HEIGHT	16	//分割幅

#define PLAYER_YOKO_CNT	3
#define PLAYER_TATE_CNT	4
#define TXT_POSE_YOKO_CNT	1
#define TXT_POSE_TATE_CNT	6

#define PLAYER_ALL_CNT	PLAYER_YOKO_CNT * PLAYER_TATE_CNT
#define	TXT_POSE_ALL_CNT TXT_POSE_YOKO_CNT * TXT_POSE_TATE_CNT

#define PLAYER_ANI_SPEED 5.0
#define TXT_POSE_SPEED	10.0

//########## マクロ定義：エラーメッセージ##########
#define ANIMATION_ERROR_TTILE	"ANIMATION_ERROR"						//エラータイトル
#define ANIMATION_ERROR_MSG		"アニメーションが読み込めませんでした"	//エラーメッセージ

//########## 列挙型 ############
enum DIST {
	FLONT=0,	//前向き
	LEFT=3,		//左向き
	RIGHT=6,	//右向き
	BACK=9		//後ろ向き
};

//########## クラスの定義 ##########
class ANIMATION
{
private:
	std::string FilePath;	//パス
	std::string FileName;	//名前

	std::vector<std::vector<int>> Handle;				//ハンドル
	std::vector<int>::iterator Handle_itr;	//ハンドルのイテレータ(ポインタ)

	std::vector<int> Width;					//幅
	std::vector<int> Height;				//高さ

	std::vector<double> NextChangeSpeed;	//アニメーションを変更する速さ(秒)
	std::vector<int> ChangeMaxCnt;			//アニメーションするフレームの最大値
	std::vector<int> ChangeCnt;				//アニメーションするフレームのカウント
	std::vector<int> ChangeCntNow;			//チェンジカウント

	std::vector<bool> IsAnimeLoop;			//アニメーションはループする？
	std::vector<bool> IsAnimeStop;			//アニメーションはストップしたか？

	bool IsLoad;				//読み込めたか？
	
public:
	ANIMATION(const char *, const char *, int, int, int, int, int, double,bool,int size=1);	//コンストラクタ
	virtual ~ANIMATION();	//デストラクタ

	std::string GetFileName(void);	//名前を取得

	int GetWidth(int=0);				//幅を取得
	int GetHeight(int=0);			//高さを取得

	bool GetIsLoad();			//読み込めた？

	bool GetIsAnimeStop(int=0);		//アニメーションはストップしたかを取得

	void ResetIsAnime(int=0);		//アニメーションがストップしたかをリセット

	void Draw(int,int,int,bool,int=0);	//画像を描画

	void DrawAnime(int, int,int=0);		//アニメーション描画

	bool Add(const char *, const char *, int, int, int, int, int, double, bool, int = 0);	//アニメーション追加

	void SetSize(void);				//サイズを設定する

};

