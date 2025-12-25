//Question.cpp
//問題関係の全ての基になるクラス

//############### ヘッダファイル読み込み #######################
#include "Question.hpp"

//############### クラス定義 ####################

//インスタンスを生成
Image* Question::img_kokuban;					//黒板の画像
vector<vector<int>> Question::CalcType_Table;	//各ゲームモードの計算の種類のテーブル

//コンストラクタ
Question::Question(int mode, int level)
{
	//メンバー初期化
	Anser = 0;				//答え
	Q_Text = "";			//問題文
	IsCreate = false;		//問題を作成したか
	IsAnswerd = false;		//回答済みか

	if (CalcType_Table.empty())	//情報を作成していなければ
	{
		//テーブル作成
		CreateTable();		//テーブル作成

	}

	if (img_kokuban == NULL)	//黒板の画像を生成していなければ
	{
		img_kokuban = new Image(Q_IMAGE_DIR, Q_IMAGE_KOKUBAN_NAME);	//黒板の画像を生成
	}

	Create(mode, level);	//問題の作成

	IsCreate = true;		//問題を作成した

}

//デストラクタ
Question::~Question(){}

//問題作成
void Question::Create(int mode, int level)
{

	int min = VALUE_MIN, max = 0;		//問題の最小値、最大値

	vector<int> value, type;	//値、計算の種類
	const vector<int> value_num = { EASY_NUM,NR_NUM,HARD_NUM };	//値の数

	SetCalcType(mode, level, value_num.at(level), &type);	//計算の種類を設定

	for (int i = 0; i < value_num.at(level); ++i)
	{
		max = GetMax(level, value);				//最大値設定
		int rand = GetRand(max - min) + min;	//値をランダムで生成

		value.push_back(rand);	//値を追加
	}


	vector<int> order;		//計算の順番
	SetOrder(type, &order);	//計算の順番を設定

	CreateQuestion(value, type, order);	//問題を生成

	IsCreate = true;	//問題を作成した

	//vectorの解放
	vector<int> v;
	value.swap(v);
	vector<int> v2;
	type.swap(v2);
	vector<int> v3;
	order.swap(v3);

}

//計算の種類を設定
void Question::SetCalcType(int mode, int level, int num, vector<int>* calc_type)
{

	for (int i = 0; i < num - 1; ++i)
	{
		int rand = GetRand(CalcType_Table.at(mode).size() - 1);		//乱数生成
		calc_type->push_back(CalcType_Table.at(mode).at(rand));		//計算の種類を設定
	}

}

//計算の順番を設定
void Question::SetOrder(vector<int> calc_type, vector<int>* order)
{
	vector<bool> set_flg;	//設定済みか

	for (int i = 0; i < calc_type.size(); ++i)
		set_flg.push_back(false);	//初期化

	for (int i = 0; i < calc_type.size(); ++i)
	{
		if (calc_type.at(i) == CALC_PRODUCT || calc_type.at(i) == CALC_DEALER)	//掛け算か、割り算だったら
		{
			order->push_back(i);	//計算の順番を設定
			set_flg.at(i) = true;	//設定済み
		}

	}

	for (int i = 0; i < calc_type.size(); ++i)
	{
		if (!set_flg.at(i))	//設定済みじゃなければ
		{
			order->push_back(i);	//計算の順番を設定
			set_flg.at(i) = true;	//設定済み
		}
	}

	//vectorの解放
	vector<bool> v;
	set_flg.swap(v);

}

//最大値取得
int Question::GetMax(int level, vector<int> value)
{

	//レベル毎の最大値
	//const int value_max[GAME_LEVEL_MAX] = { EASY_VALUE_MAX ,NORMAL_VALUE_MAX ,HARD_VALUE_MAX };
	const vector<int> val_max = { EASY_VALUE_MAX ,NORMAL_VALUE_MAX ,HARD_VALUE_MAX };

	if (value.empty())	//最初の取得なら
	{
		//定数を返す
		return val_max[level];	//ゲームレベル毎の最大値を返す

	}
	else	//最初じゃなければ
	{
		return GetRand(value.back());	//最後の値を最大値とした乱数を返す
	}
}

//それぞれの問題を作成
void Question::CreateQuestion(vector<int>calc_value, vector<int>calc_type, vector<int> order)
{

	auto type_cp = calc_type;	//種類のコピー
	auto value_cp = calc_value;	//値のコピー
	auto order_cp = order;		//順番のコピー

	for (int i = 0; i < order.size(); ++i)
	{
		switch (calc_type.at(order.at(i)))	//計算の種類ごとに分岐
		{

		case CALC_SUM:	//足し算

			calc_value.at(order.at(i) + 1) = calc_value.at(order.at(i)) + calc_value.at(order.at(i) + 1);	//指定された値と、その次の値で計算

			break; //足し算

		case CALC_DIFFERENCE:	//引き算

			calc_value.at(order.at(i) + 1) = calc_value.at(order.at(i)) - calc_value.at(order.at(i) + 1);	//指定された値と、その次の値で計算

			break; //引き算

		case CALC_PRODUCT:	//掛け算

			calc_value.at(order.at(i) + 1) = calc_value.at(order.at(i)) * calc_value.at(order.at(i) + 1);	//指定された値と、その次の値で計算

			break; //掛け算

		case CALC_DEALER:	//割り算

			//値の調整
			while (calc_value.at(order.at(i)) % calc_value.at(order.at(i) + 1) != 0)	//割り切れない間
			{
				//割り切れる値になるまで、値を減らす
				--calc_value.at(order.at(i) + 1);
			}
			value_cp.at(order_cp.at(i) + 1) = calc_value.at(order.at(i) + 1);	//値を変化させたため、コピーの方を更新する
			calc_value.at(order.at(i) + 1) = calc_value.at(order.at(i)) / calc_value.at(order.at(i) + 1);	//指定された値と、その次の値で計算

			break; //割り算


		default:
			break;
		}

		//計算済みの要素を削除
		calc_value.erase(calc_value.begin() + order.at(i));		//計算済みの値を削除
		calc_type.erase(calc_type.begin() + order.at(i));		//計算済みの計算種類を削除

		//計算済みの要素を削除したため、計算順番を一つずつ前に繰り上げる
		for (auto itr = order.begin(); itr != order.end(); ++itr)
		{
			if (*itr != 0)	//先頭じゃなければ
				--* itr;
		}

	}

	SetText(value_cp, type_cp, order_cp);	//問題文のテキストを設定

	Anser = calc_value.front();	//先頭に全ての計算結果が格納されているため、それを答えに設定

}

//各ゲームモードの計算の種類のテーブル
void Question::CreateTable()
{

	vector<int> work;	//作業用

	//**************************** 各ゲームモードの計算の種類のテーブル **************************
	//足し算モード
	work.push_back(CALC_SUM);		//足し算
	CalcType_Table.push_back(work);	//足し算モードの計算の種類の選択肢を追加
	work.clear();					//中身をクリア

	//引き算モード
	work.push_back(CALC_DIFFERENCE);//引き算
	CalcType_Table.push_back(work);	//引き算モードの計算の種類の選択肢を追加
	work.clear();					//中身をクリア

	//掛け算モード
	work.push_back(CALC_PRODUCT);	//掛け算
	CalcType_Table.push_back(work);	//掛け算モードの計算の種類の選択肢を追加
	work.clear();					//中身をクリア

	//割り算モード
	work.push_back(CALC_DEALER);	//割り算
	CalcType_Table.push_back(work);	//割り算モードの計算の種類の選択肢を追加
	work.clear();					//中身をクリア

	//足し算、引き算モード
	work.push_back(CALC_SUM);		//足し算
	work.push_back(CALC_DIFFERENCE);//引き算
	CalcType_Table.push_back(work);	//足し算、引き算モードの計算の種類の選択肢を追加
	work.clear();					//中身をクリア

	//掛け算、割り算モード
	work.push_back(CALC_PRODUCT);	//掛け算
	work.push_back(CALC_DEALER);	//割り算
	CalcType_Table.push_back(work);	//掛け算、割り算モードの計算の種類の選択肢を追加
	work.clear();					//中身をクリア

	//足し算、掛け算モード
	work.push_back(CALC_SUM);		//足し算
	work.push_back(CALC_PRODUCT);	//掛け算
	CalcType_Table.push_back(work);	//足し算、掛け算モードの計算の種類の選択肢を追加
	work.clear();					//中身をクリア

	//+/モード
	work.push_back(CALC_SUM);		//+
	work.push_back(CALC_DEALER);	// /
	CalcType_Table.push_back(work);	//+/モードの計算の種類の選択肢を追加
	work.clear();					//中身をクリア

	//-*モード
	work.push_back(CALC_DIFFERENCE);//-
	work.push_back(CALC_PRODUCT);	//*
	CalcType_Table.push_back(work);	//-*モードの計算の種類の選択肢を追加
	work.clear();					//中身をクリア

	//+-*モード
	work.push_back(CALC_SUM);		//+
	work.push_back(CALC_DIFFERENCE);//-
	work.push_back(CALC_PRODUCT);	//*
	CalcType_Table.push_back(work);	//+-*モードの計算の種類の選択肢を追加
	work.clear();					//中身をクリア

	//+-/モード
	work.push_back(CALC_SUM);		//+
	work.push_back(CALC_DIFFERENCE);//-
	work.push_back(CALC_DEALER);	///
	CalcType_Table.push_back(work);	//+-/モードの計算の種類の選択肢を追加
	work.clear();					//中身をクリア

	//allモード
	work.push_back(CALC_SUM);		//+
	work.push_back(CALC_DIFFERENCE);//-
	work.push_back(CALC_PRODUCT);	//*
	work.push_back(CALC_DEALER);	///
	CalcType_Table.push_back(work);	//allモードの計算の種類の選択肢を追加
	work.clear();					//中身をクリア

	//vectorの解放
	vector<int> v;
	work.swap(v);


}

//問題文のテキストを設定
void Question::SetText(vector<int> value, vector<int> type, vector<int> order)
{

	//記号のテーブル作成
	static vector<string> SymbolTable = { "＋","－","×","÷" };

	Q_Text = std::to_string(value.front());	//先頭の値を問題文に設定

	for (int i = 0; i < type.size(); ++i)
	{
		Q_Text += SymbolTable.at(type.at(i));		//記号を問題文に追加
		Q_Text += std::to_string(value.at(i + 1));	//値を問題文に追加(最初の値は既に追加されているため、+1した要素の値を設定)
	}

	Q_Text += "＝？";			//問題文追加

}

//問題を描画する
void Question::DrawQuestion()
{

	img_kokuban->Draw(GAME_LEFT, Q_IMG_DRAW_Y);		//黒板の画像を描画

	int Strlen = strlen(Q_Text.c_str());					//文字列長さを取得
	int Width = GetDrawStringWidthToHandle(Q_Text.c_str(), Strlen, Font::GetNowHandle());	//横幅取得

	
	DrawFormatStringToHandle((GAME_WIDTH / 2) - (Width / 2), Q_DRAW_Y, COLOR_WHITE, Font::GetNowHandle(), "%s", Q_Text.c_str());	//問題文を描画

	return;
}

//正解か判定する
/*
引数：int：プレイヤーの答え
戻り値：bool：true 正解：false 不正解
*/
bool Question::JudgAnser(int ans)
{
	if (Anser == ans)			//プレイヤーの回答が、答えと一緒だったら
	{
		IsCreate = false;		//問題を作成したか、リセット
		return true;			//正解
	}
	else						//一緒じゃなかったら
		return false;			//不正解
}

//問題を作成したか取得
bool Question::GetIsCreate()
{
	return IsCreate;
}
