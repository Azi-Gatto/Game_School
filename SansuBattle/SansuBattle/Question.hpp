//Question.hpp
//問題関係の全ての基になるクラス

#pragma once

//################# ヘッダファイル読み込み ###############
#include "Global.hpp"
#include "Image.hpp"

//################# マクロ定義 #################
#define Q_IMG_DRAW_Y 490	//問題の画像（黒板）描画Y位置
#define Q_DRAW_Y 520		//問題の描画Y位置

#define EASY_VALUE_MAX 15	//簡単レベルの問題の最大値
#define NORMAL_VALUE_MAX 20	//普通レベルの問題の最大値
#define HARD_VALUE_MAX	25	//難しいレベルの問題の最大値
#define EASY_NUM	2		//簡単レベルの数字の数
#define NR_NUM		3		//普通レベルの数字の数
#define HARD_NUM	4		//難しいレベルの数字の数

#define VALUE_MIN	3		//値の最小値

#define Q_IMAGE_DIR		R"(.\Image\Question)"		//問題関係の画像のディレクトリ

#define	Q_IMAGE_KOKUBAN_NAME	R"(\kokuban.png)"	//黒板の画像の名前

//################# 列挙型 ###################
enum CALC_KIND
{
	CALC_SUM,			//足し算
	CALC_DIFFERENCE,	//引き算
	CALC_PRODUCT,		//掛け算
	CALC_DEALER,		//割り算
	CALC_MAX			//計算の種類の個数
};	//計算の種類

using std::vector;
using std::string;

//################# クラス定義 #################
class Question
{
private:

	static Image* img_kokuban;			//黒板の画像
	static vector<vector<int>> CalcType_Table;	//各ゲームモードの計算の種類のテーブル

	string Q_Text;				//問題文
	int Anser;					//答え
	bool IsCreate;				//問題を作成したか

	bool IsAnswerd;				//回答済みか

	void SetCalcType(int, int,int, vector<int>*);				//計算の種類を設定
	void SetOrder(vector<int>, vector<int>*);					//計算の順番を設定
	int GetMax(int, vector<int>);								//最大値取得
	void CreateQuestion(vector<int>, vector<int>, vector<int>);	//問題を作成
	void CreateTable();											//各ゲームモードの計算の種類のテーブルを作成
	void SetText(vector<int>, vector<int>, vector<int>);		//問題文のテキストを設定
	void Create(int, int);										//問題作成

public:

	Question(int, int);			//コンストラクタ
	~Question();				//デストラクタ


	void DrawQuestion();		//問題を描画する

	bool JudgAnser(int);		//正解か判定する
	bool GetIsCreate();			//問題を作成したか取得

};
