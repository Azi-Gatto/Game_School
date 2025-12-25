//EFFECT.cpp
//エフェクトクラス

//################## ヘッダファイル読み込み ##################
#include "EFFECT.hpp"

//################## クラス定義 #######################

//コンストラクタ
/*
引　数：const char *：画像のディレクトリ
引　数：const char *：画像の名前
引　数：int：画像の総分割数
引　数：int：画像の横向きの分割数
引　数：int：画像の縦向きの分割数
引　数：int：画像の分割された横の大きさ
引　数：int：画像の分割された縦の大きさ
引　数：double：次の画像に変更する速さ
引　数：bool：アニメーションをループするかどうか
引　数：int：サイズ
*/
EFFECT::EFFECT(const char *dir, const char *name, int SplitNumALL, int SpritNumX, int SplitNumY, int SplitWidth, int SplitHeight, double changeSpeed, bool IsLoop,int size)
{
	//メンバ変数初期化
	this->Handle.resize(size);		//エフェクトの種類数でサイズ変更
	this->Width.resize(size);		//エフェクトの種類数でサイズ変更
	this->Height.resize(size);		//エフェクトの種類数でサイズ変更
	this->IsAnimeLoop.resize(size);	//エフェクトの種類数でサイズ変更
	this->IsAnimeStop.resize(size);	//エフェクトの種類数でサイズ変更

	this->Handle[0].resize(SplitNumALL);	//分割総数でサイズ変更
	this->Handle_itr = this->Handle[0].begin();	//先頭要素を代入

	this->ChangeMaxCnt = (int)(changeSpeed * fps->Getvalue());	//アニメーションするフレームの最大値
	this->ChangeCnt = 0;	//アニメーションするフレームのカウント

	this->IsAnimeLoop[0] = IsLoop;		//アニメーションはループする？
	this->IsAnimeStop[0] = false;		//アニメーションを動かす

	this->IsLoad = false;			//読み込めたか？
	this->IsDrawEnd = false;		//描画終了したか?

	//画像を読み込み
	std::string LoadfilePath;		//画像のファイルパスを作成
	LoadfilePath += dir;
	LoadfilePath += name;

	//画像を分割して読み込み
	LoadDivGraph(LoadfilePath.c_str(), SplitNumALL, SpritNumX, SplitNumY, SplitWidth, SplitHeight, &this->Handle[0][0]);

	if (this->Handle[0][0] == -1)	//画像が読み込めなかったとき
	{
		std::string ErrorMsg(EFFECT_ERROR_MSG);	//エラーメッセージ作成
		ErrorMsg += TEXT('\n');						//改行
		ErrorMsg += LoadfilePath;					//画像のパス

		MessageBox(
			NULL,
			ErrorMsg.c_str(),	//char * を返す
			TEXT(EFFECT_ERROR_TTILE),
			MB_OK);

		return;
	}

	this->NextChangeSpeed = changeSpeed;	//画像を変える速さ

	this->IsLoad = true;		//読み込めた

	return;

}

//デストラクタ
EFFECT::~EFFECT()
{
	for (int i = 0; i < MAGIC_EFFECT_KIND; ++i)
	{
		DeleteGraph(this->Handle[i][0]);
	}

	//vectorのメモリ解放を行う
	std::vector<std::vector<int>> v;			//空のvectorを作成する
	this->Handle.swap(v);						//空と中身を入れ替える

	std::vector<int> v2;
	this->Width.swap(v2);

	std::vector<int> v3;
	this->Height.swap(v3);

	std::vector<bool> v4;
	this->IsAnimeLoop.swap(v4);

	std::vector<bool> v5;
	this->IsAnimeStop.swap(v5);

	return;

}

//幅を取得
int EFFECT::GetWidth(int type)
{
	return this->Width[type];
}

//高さを取得
int EFFECT::GetHeight(int type)
{
	return this->Height[type];
}

//読み込めた？
bool EFFECT::GetIsLoad(void)
{
	return this->IsLoad;
}

//アニメーションはストップしたかを取得
bool  EFFECT::GetIsAnimeStop(int type)
{
	return this->IsAnimeStop[type];
}

//描画終了したかどうか取得
bool EFFECT::GetIsDrawEnd()
{
	return this->IsDrawEnd;
}

//描画終了したか設定
void EFFECT::SetIsDrawEnd(bool isend)
{
	this->IsDrawEnd = isend;
	return;
}

//アニメーションがストップしたかをリセット
void EFFECT::ResetIsAnime(int type)
{
	this->IsAnimeStop[type] = false;
	this->IsDrawEnd = false;		
	return;
}

//描画
/*
引数：int：Xの描画位置
引数：int：Yの描画位置
引数：int：描画するエフェクトの種類
*/
void EFFECT::Draw(int x, int y,int type)
{


	static int cnt = 0;		//フェードアウト用
	static int cntMax = 60;	//フェードアウト用
	static bool flg = false;//フェードアウト終了フラグ

	//60フレーム分、待つ
	if (cnt < cntMax)
	{
		cnt++;	//カウントアップ
	}
	else
	{
		flg = true;	//フェードアウト処理終了
	}

	//フェードアウトの処理
	double ToukaPercent = cnt / (double)cntMax;//透過％を求める
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, ToukaPercent * 255);	//透過させる
	DrawBox(0, 0, GAME_WIDTH, GAME_HEIGHT, GetColor(0, 0, 0), TRUE);	//真っ暗な画面にする
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);	//透過をやめる

	if (flg)		//フェードアウトが終了していたら
	{
			if (this->IsAnimeStop[type] == false)	//アニメーションをストップさせないなら
			{
				DrawGraph(x, y, *this->Handle_itr, TRUE);	//イテレータ(ポインタ)を使用して描画
			}
			else
			{
				this->IsDrawEnd = true;		//描画終了
				flg = false;	//フェードアウトフラグリセット
				cnt = 0;		//フェードアウトカウントリセット
			}

			if (this->ChangeCnt == this->ChangeMaxCnt)	//次の画像を表示する時がきたら
			{
				//this->Handle.end()は、最後の要素の１個次のイテレータを返すので、-1している。
				if (this->Handle_itr == this->Handle[type].end() - 1)	//イテレータ(ポインタ)が最後の要素のときは
				{
					//アニメーションをループしないなら
					if (this->IsAnimeLoop[type] == false)
					{
						this->IsAnimeStop[type] = true;	//アニメーションを止める
					}

					//次回の描画に備えて、先頭の画像に戻しておく
					this->Handle_itr = this->Handle[type].begin();	//イテレータ(ポインタ)を要素の最初に戻す
				}
				else
				{
					this->Handle_itr++;	//次のイテレータ(ポインタ)(次の画像)に移動する
				}

				this->ChangeCnt = 0;	//カウント初期化
			}
			else
			{
				this->ChangeCnt++;	//カウントアップ
			}

	}
	else
	{
		this->Handle_itr = this->Handle[type].begin();		//指定されたエフェクトタイプのハンドルを代入
	}

	return;

}

//描画（フェードアウトなし）
/*
引数：int：Xの描画位置
引数：int：Yの描画位置
引数：int：描画するエフェクトの種類
*/
void EFFECT::DrawNormal(int x, int y, int type)
{
	static bool setflg = false;	//ハンドル設定フラグ
	if (setflg == false)
	{
		this->Handle_itr = this->Handle[type].begin();		//指定されたエフェクトタイプのハンドルを代入
		setflg = true;	//ハンドル設定済み
	}

		if (this->IsAnimeStop[type] == false)	//アニメーションをストップさせないなら
		{
			DrawGraph(x, y, *this->Handle_itr, TRUE);	//イテレータ(ポインタ)を使用して描画
		}
		else
		{
			this->IsDrawEnd = true;		//描画終了
			setflg = false;				//ハンドル未設定
		}

		if (this->ChangeCnt == this->ChangeMaxCnt)	//次の画像を表示する時がきたら
		{
			//this->Handle.end()は、最後の要素の１個次のイテレータを返すので、-1している。
			if (this->Handle_itr == this->Handle[type].end() - 1)	//イテレータ(ポインタ)が最後の要素のときは
			{
				//アニメーションをループしないなら
				if (this->IsAnimeLoop[type] == false)
				{
					this->IsAnimeStop[type] = true;	//アニメーションを止める
				}

				//次回の描画に備えて、先頭の画像に戻しておく
				this->Handle_itr = this->Handle[type].begin();	//イテレータ(ポインタ)を要素の最初に戻す
			}
			else
			{
				this->Handle_itr++;	//次のイテレータ(ポインタ)(次の画像)に移動する
			}

			this->ChangeCnt = 0;	//カウント初期化
		}
		else
		{
			this->ChangeCnt++;	//カウントアップ
		}

	return;

}


//追加
/*
引　数：const char *：画像のディレクトリ
引　数：const char *：画像の名前
引　数：int：画像の総分割数
引　数：int：画像の横向きの分割数
引　数：int：画像の縦向きの分割数
引　数：int：画像の分割された横の大きさ
引　数：int：画像の分割された縦の大きさ
引　数：double：次の画像に変更する速さ
引　数：bool：アニメーションをループするかどうか
引　数：int：追加するエフェクトの種類
*/
bool EFFECT::Add(const char *dir, const char *name, int SplitNumALL, int SpritNumX, int SplitNumY, int SplitWidth, int SplitHeight, double changeSpeed, bool IsLoop, int type)
{
	this->IsAnimeLoop[type] = IsLoop;		//アニメーションはループする？
	this->IsAnimeStop[type] = false;		//アニメーションを動かす

	this->Handle[type].resize(SplitNumALL);	//分割総数でサイズ変更

	//画像を読み込み
	std::string LoadfilePath;		//画像のファイルパスを作成
	LoadfilePath += dir;
	LoadfilePath += name;

	//画像を分割して読み込み
	LoadDivGraph(LoadfilePath.c_str(), SplitNumALL, SpritNumX, SplitNumY, SplitWidth, SplitHeight, &this->Handle[type][0]);

	if (this->Handle[type][0] == -1)	//画像が読み込めなかったとき
	{
		std::string ErrorMsg(EFFECT_ERROR_MSG);	//エラーメッセージ作成
		ErrorMsg += TEXT('\n');						//改行
		ErrorMsg += LoadfilePath;					//画像のパス

		MessageBox(
			NULL,
			ErrorMsg.c_str(),	//char * を返す
			TEXT(EFFECT_ERROR_TTILE),
			MB_OK);

		return false;		//読み込み失敗
	}

	return true;		//読み込めた

}

//サイズ設定
void EFFECT::SetSize(void)
{
	//エフェクトの数だけループさせる
	for (int i = 0; i < this->Handle.size(); ++i)
	{
		GetGraphSize(this->Handle[i][0], &this->Width[i], &this->Height[i]);	//サイズ取得
	}
}
