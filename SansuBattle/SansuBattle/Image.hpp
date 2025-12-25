/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
/* Image.cpp     																				　 */
/* 画像クラス 																					　 */

#pragma once

//########## ヘッダーファイル読み込み ##########
#include "Global.hpp"

//########## マクロ定義：画像のファイルパスと名前 ##########
#define IMG_DIR_BACK		R"(.\Image\Back)"	//背景画像のファイルの場所

#define IMG_NAME_TITLE		R"(\title.jpg)"		//タイトル画面の背景画像の名前
#define IMG_NAME_SELECT		R"(\select.jpg)"	//選択画面の背景画像の名前
#define IMG_NAME_PLAY		R"(\play.jpg)"		//プレイ画面の背景画像の名前
#define IMG_NAME_RANKING	R"(\ranking.jpg)"	//ランキング画面の背景画像の名前

#define FADE_MAX_CNT	60	//フェード処理のカウント最大値
#define TOUKA_MAX_VALUE	255	//透過の最大値

//########## マクロ定義：エラーメッセージ##########
#define IMAGE_ERROR_TITLE "IMAGE_ERROR"					//エラータイトル
#define IMAGE_ERROR_MSG	"画像が読み込めませんでした"	//エラーメッセージ

//########## 列挙型 ################
enum BACK_IMAGE
{
	TITLE_BACK,		//タイトル画面の背景画像
	PLAY_BACK,		//プレイ画面の背景画像
	RANKING_BACK	//ランキング画面
};

using std::string;

//########## クラスの定義 ##########
class Image
{
private:
	string FilePath;	//パス
	string FileName;	//名前

	int Handle;			//ハンドル

	int Width;			//幅
	int Height;			//高さ

	bool IsLoad;		//読み込めたか？
	bool IsDraw;		//描画してよいか
	bool IsFade;		//フェードアウトするか
	bool FadeEnd;		//フェードエフェクトが終わったか

public:
	Image(const char *,const char *);	//コンストラクタ
	Image();							//コンストラクタ
	virtual ~Image();					//デストラクタ

	bool Load(const char*, const char*);//読み込み

	string GetFileName(void);	//名前を取得

	void SetInit(void);				//サイズをセット

	int GetWidth();		//幅を取得
	int GetHeight();	//高さを取得

	bool GetIsLoad(void);			//読み込めた？
	bool GetIsDraw();				//描画してよいか取得
	void SetIsDraw(bool);			//描画してよいか設定

	void Draw(int, int);		//画像を描画
	void DrawCenter();			//画像を描画（中央）
	void DrawCenterY(int);		//画像を描画（上下中央）
	void DrawCenterX(int);		//画像を描画（左右中央）

	void SetIsFade(bool);		//フェードアウトするか設定
	bool GetFadeEnd();			//フェードエフェクトが終了しているか取得

};

