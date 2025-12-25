/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
/* ANIMATION.cpp     																			　 */
/* アニメーションクラス 																		　 */

//########## ヘッダーファイル読み込み ##########
#include "ANIMATION.hpp"

//########## クラスの定義 ##########

//コンストラクタ
//コンストラクタ
//引　数：const char *：画像のディレクトリ
//引　数：const char *：画像の名前
//引　数：int：画像の総分割数
//引　数：int：画像の横向きの分割数
//引　数：int：画像の縦向きの分割数
//引　数：int：画像の分割された横の大きさ
//引　数：int：画像の分割された縦の大きさ
//引　数：double：次の画像に変更する速さ
//引　数：bool：アニメーションをループするかどうか
ANIMATION::ANIMATION(const char *dir, const char *name, int SplitNumALL, int SpritNumX, int SplitNumY, int SplitWidth, int SplitHeight, double changeSpeed, bool IsLoop,int size)
{
	//メンバ変数を初期化
	this->FilePath = "";	//パス
	this->FileName = "";	//名前
	this->Handle.resize(size);

	this->Handle[0].resize(SplitNumALL);			//resize：vectorの要素数を変更する
	this->Handle_itr = this->Handle[0].begin();		//先頭のポインタを入れる

	this->ChangeMaxCnt.push_back(SpritNumX);
	this->ChangeCnt.push_back(0);
	this->ChangeCntNow.push_back(0);

	this->IsAnimeLoop.push_back(IsLoop);
	this->IsAnimeStop.push_back(false);

	this->Width.push_back(0);
	this->Height.push_back(0);

	this->IsLoad = false;			//読み込めたか？

	//画像を読み込み
	std::string LoadfilePath;		//画像のファイルパスを作成
	LoadfilePath += dir;
	LoadfilePath += name;

	//画像を分割して読み込み
	LoadDivGraph(LoadfilePath.c_str(), SplitNumALL, SpritNumX, SplitNumY, SplitWidth, SplitHeight, &this->Handle[0][0]);

	if (this->Handle[0][0] == -1)	//画像が読み込めなかったとき
	{
		std::string ErrorMsg(ANIMATION_ERROR_MSG);	//エラーメッセージ作成
		ErrorMsg += TEXT('\n');						//改行
		ErrorMsg += LoadfilePath;					//画像のパス

		MessageBox(
			NULL,
			ErrorMsg.c_str(),	//char * を返す
			TEXT(ANIMATION_ERROR_TTILE),
			MB_OK);

		return;
	}

	this->FilePath = LoadfilePath;		//画像のパスを設定
	this->FileName = name;				//画像の名前を設定

	//GetGraphSize(
	//	this->Handle[0][0],	//このハンドルの画像の大きさを取得
	//	&this->Width[0],		//Widthのアドレスを渡す
	//	&this->Height[0]		//Heightのアドレスを渡す
	//);

	this->NextChangeSpeed.push_back(changeSpeed);

	this->IsLoad = true;		//読み込めた

	return;
}

//デストラクタ
ANIMATION::~ANIMATION()
{

	for (int i = 0; i < this->Handle.size(); ++i)
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

	std::vector<int> v6;
	this->ChangeMaxCnt.swap(v6);

	std::vector<int> v7;
	this->ChangeCnt.swap(v7);

	std::vector<double> v8;
	this->NextChangeSpeed.swap(v8);

	return;
}

//ファイルの名前を取得
std::string ANIMATION::GetFileName(void)
{
	return this->FileName;
}

//幅を取得
int ANIMATION::GetWidth(int type)
{
	return this->Width[type];
}

//高さを取得
int ANIMATION::GetHeight(int type)
{
	return this->Height[type];
}

//読み込めた？
bool ANIMATION::GetIsLoad(void)
{
	return this->IsLoad;
}

//アニメーションはストップしたかを取得
bool  ANIMATION::GetIsAnimeStop(int type)
{
	return this->IsAnimeStop[type];
}

//アニメーションがストップしたかをリセット
void ANIMATION::ResetIsAnime(int type)
{
	this->IsAnimeStop[type] = false;
	return;
}

//画像を描画
//引数：int ：X座標
//引数：int ：Y座標
//引数：int ：移動方向
//引数：bool：アニメーションするか
void ANIMATION::Draw(int X, int Y,int Dist,bool animetion,int type)
{
	if (animetion)	//アニメーションで描画する場合
	{
		if (*this->Handle_itr == this->Handle[type][Dist+this->ChangeCnt[type]])
		{
			if (this->ChangeCntNow[type] < this->NextChangeSpeed[type])
			{
				this->ChangeCntNow[type]++;
				DrawGraph(X, Y, *this->Handle_itr, TRUE);	//描画
			}
			else
			{
				if (this->ChangeCnt[type] < this->ChangeMaxCnt[type] - 1)	//最後の画像じゃないとき
				{
					DrawGraph(X, Y, *this->Handle_itr, TRUE);	//描画
					this->ChangeCnt[type]++; //カウントアップ
					this->Handle_itr++;//次の画像

				}
				else
				{
					DrawGraph(X, Y, *this->Handle_itr, TRUE);	//描画
					this->ChangeCnt[type] = 0;	//カウントリセット
				}
				this->ChangeCntNow[type] = 0;		//カウントリセット

			}

		}
		else
		{
			DrawGraph(X, Y, *this->Handle_itr, TRUE);	//描画
			this->Handle_itr = this->Handle[type].begin() + Dist + this->ChangeCnt[type];
		}

	}
	else	//アニメーション描画じゃないとき
	{
		this->Handle_itr = this->Handle[type].begin() + Dist + 1;	//止まっているときの画像
		DrawGraph(X, Y, *this->Handle_itr, TRUE);	//描画
	}
	

	return;
}

//アニメーション描画
void ANIMATION::DrawAnime(int x, int y,int type)
{
	if (this->IsAnimeStop[type] == false)	//アニメーションをストップさせないなら
	{
		DrawGraph(x, y, *this->Handle_itr, TRUE);	//イテレータ(ポインタ)を使用して描画
	}
	else
	{
		
	}

	if (this->ChangeCnt[type] == this->NextChangeSpeed[type])	//次の画像を表示する時がきたら
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

		this->ChangeCnt[type] = 0;	//カウント初期化
	}
	else
	{
		this->ChangeCnt[type]++;	//カウントアップ
	}

}

//アニメーション追加
bool ANIMATION::Add(const char *dir, const char *name, int SplitNumALL, int SpritNumX, int SplitNumY, int SplitWidth, int SplitHeight, double changeSpeed, bool IsLoop, int type)
{
	this->IsAnimeLoop[type] = IsLoop;		//アニメーションはループする？
	this->IsAnimeStop[type] = false;		//アニメーションを動かす

	//画像を読み込み
	std::string LoadfilePath;		//画像のファイルパスを作成
	LoadfilePath += dir;
	LoadfilePath += name;

	//画像を分割して読み込み
	LoadDivGraph(LoadfilePath.c_str(), SplitNumALL, SpritNumX, SplitNumY, SplitWidth, SplitHeight, &this->Handle[type][0]);

	if (this->Handle[type][0] == -1)	//画像が読み込めなかったとき
	{
		std::string ErrorMsg(ANIMATION_ERROR_MSG);	//エラーメッセージ作成
		ErrorMsg += TEXT('\n');						//改行
		ErrorMsg += LoadfilePath;					//画像のパス

		MessageBox(
			NULL,
			ErrorMsg.c_str(),	//char * を返す
			TEXT(ANIMATION_ERROR_TTILE),
			MB_OK);

		return false;		//読み込み失敗
	}

	//GetGraphSize(
	//	this->Handle[type][0],	//このハンドルの画像の大きさを取得
	//	&this->Width[0],		//Widthのアドレスを渡す
	//	&this->Height[0]		//Heightのアドレスを渡す
	//);

	return true;		//読み込めた

}

//サイズを設定する
void ANIMATION::SetSize(void)
{
	for (int i = 0; i < this->Handle.size(); ++i)
	{
		GetGraphSize(this->Handle[i][0], &this->Width[i], &this->Height[i]);		//画像サイズ取得
	}

	return;
}
