/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
/* Image.cpp     																				　 */
/*       																						　 */

//########## ヘッダーファイル読み込み ##########
#include "Image.hpp"

//########## クラスの定義 ##########

//コンストラクタ
//引　数：const char *：画像のディレクトリ
//引　数：const char *：画像の名前
Image::Image(const char *dir,const char *name)
{
	//メンバ変数を初期化
	FilePath = "";	//パス
	FileName = "";	//名前
	
	IsLoad = false;	//読み込めたか？

	//画像を読み込み
	string LoadfilePath;	//画像のファイルパスを作成
	LoadfilePath += dir;
	LoadfilePath += name;

	Handle = LoadGraph(LoadfilePath.c_str());//画像を読み込み
	
	if (Handle == -1)	//画像が読み込めなかったとき
	{
		string ErroeMsg(IMAGE_ERROR_MSG);	//エラーメッセージ作成
		ErroeMsg += TEXT('\n');				//改行
		ErroeMsg += LoadfilePath;			//画像のパス

		MessageBox(
			NULL, 
			ErroeMsg.c_str(),	//char * を返す
			TEXT(IMAGE_ERROR_TITLE),
			MB_OK);

		return;
	}

	FilePath = LoadfilePath;		//画像のパスを設定
	FileName = name;				//画像の名前を設定

	IsLoad = true;		//読み込めた

	IsDraw = true;	//描画してよい

	IsFade = false;	//フェードアウトしない
	FadeEnd = false;//フェードエフェクトが終わっていない
}

//コンストラクタ
Image::Image()
{
	//メンバ変数を初期化
	FilePath = "";	//パス
	FileName = "";	//名前
	IsLoad = false;	//読み込めたか？
	Handle = 0;
	IsDraw = true;	//描画してよい
	IsFade = false;	//フェードアウトしない
	FadeEnd = false;//フェードエフェクトが終わっていない

}

//デストラクタ
Image::~Image()
{
	DeleteGraph(Handle);	//読み込んだ画像を削除
}

//読み込み
bool Image::Load(const char* dir, const char* name)
{
	//メンバ変数を初期化
	FilePath = "";	//パス
	FileName = "";	//名前

	IsLoad = false;	//読み込めたか？

	//画像を読み込み
	string LoadfilePath;	//画像のファイルパスを作成
	LoadfilePath += dir;
	LoadfilePath += name;

	Handle = LoadGraph(LoadfilePath.c_str());//画像を読み込み

	if (Handle == -1)	//画像が読み込めなかったとき
	{
		string ErroeMsg(IMAGE_ERROR_MSG);	//エラーメッセージ作成
		ErroeMsg += TEXT('\n');				//改行
		ErroeMsg += LoadfilePath;			//画像のパス

		MessageBox(
			NULL,
			ErroeMsg.c_str(),	//char * を返す
			TEXT(IMAGE_ERROR_TITLE),
			MB_OK);

		return false;
	}

	FilePath = LoadfilePath;		//画像のパスを設定
	FileName = name;				//画像の名前を設定

	IsDraw = true;	//描画してよい

	IsFade = false;	//フェードアウトしない
	FadeEnd = false;//フェードエフェクトが終わっていない

	IsLoad = true;	//読み込めた
	return true;	//読み込めた

}

//ファイルの名前を取得
std::string Image::GetFileName(void)
{
	return FileName;
}

//サイズを設定する
void Image::SetInit(void)
{
	GetGraphSize(Handle, &Width, &Height);	//画像サイズ取得
	return;
}

//幅を取得
int Image::GetWidth()
{
	return Width;
}

//高さを取得
int Image::GetHeight()
{
	return Height;
}

//読み込めた？
bool Image::GetIsLoad(void)
{
	return IsLoad;
}

//描画してよいか取得
bool Image::GetIsDraw()
{
	return IsDraw;
}

//描画してよいか設定
void Image::SetIsDraw(bool isdraw)
{
	IsDraw = isdraw;
	FadeEnd = false;	//フェードアウト終了フラグリセット
}

//画像を描画
void Image::Draw(int x, int y)
{

	static int cnt = FADE_MAX_CNT;				//カウント用

	if (IsFade)	//フェードアウトするときは
	{
		if (!FadeEnd)	//フェードアウト終了していなければ
		{

			if (IsDraw)	//描画してよければ
			{
				
				//60フレーム分、待つ
				if (cnt > 0)
				{
					--cnt;	//カウントアップ
				}
				else
				{
					FadeEnd = true;	//フェード終了
				}

				//フェードアウトの処理
				double ToukaPercent = cnt / (double)FADE_MAX_CNT;						//透過%を計算
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, ToukaPercent * TOUKA_MAX_VALUE);	//透過させる
				DrawGraph(x, y, Handle, TRUE);											//画像を描画
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);								//透過をやめる


			}


		}
		else 		//フェードアウト終了したら
		{
			IsDraw = false;			//描画しない
			cnt = FADE_MAX_CNT;		//カウントリセット
			IsFade = false;			//フェードアウトしない
		}

	}
	else		//フェードアウトしない時は
	{
		cnt = FADE_MAX_CNT;		//カウントリセット

		if (IsDraw)	//描画してよければ
		{
			DrawGraph(x, y, Handle, TRUE);	//画像を描画
		}

	}
	

	return;

}

//画像を描画（中央）
void Image::DrawCenter()
{

	int x = 0, y = 0;	//描画するX位置,Y位置
	x = (GAME_WIDTH / 2) - (Width / 2);			//画面中央になるように計算
	y = (GAME_HEIGHT / 2) - (Height / 2);		//画面中央になるように計算

	static int cnt = FADE_MAX_CNT;				//カウント用

	if (IsFade)	//フェードアウトするときは
	{
		if (!FadeEnd)	//フェードアウト終了していなければ
		{

			if (IsDraw)	//描画してよければ
			{

				//60フレーム分、待つ
				if (cnt > 0)
				{
					--cnt;	//カウントアップ
				}
				else
				{
					FadeEnd = true;	//フェード終了
				}

				//フェードアウトの処理
				double ToukaPercent = cnt / (double)FADE_MAX_CNT;						//透過%を計算
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, ToukaPercent * TOUKA_MAX_VALUE);	//透過させる
				DrawGraph(x, y, Handle, TRUE);					//画像を描画
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);								//透過をやめる


			}


		}
		else 		//フェードアウト終了したら
		{
			IsDraw = false;	//描画しない
			cnt = FADE_MAX_CNT;				//カウントリセット
			IsFade = false;	//フェードアウトしない
		}

	}
	else		//フェードアウトしない時は
	{
		cnt = FADE_MAX_CNT;		//カウントリセット

		if (IsDraw)	//描画してよければ
		{
			DrawGraph(x, y, Handle, TRUE);	//画像を描画
		}

	}



	return;
}

//画像を描画（上下中央）
//引数：int：描画X位置
void Image::DrawCenterY(int x)
{

	int y = 0;	//描画するY位置
	y = (GAME_HEIGHT / 2) - (Height / 2);	//上下中央になるように計算

	static int cnt = FADE_MAX_CNT;				//カウント用

	if (IsFade)	//フェードアウトするときは
	{
		if (!FadeEnd)	//フェードアウト終了していなければ
		{

			if (IsDraw)	//描画してよければ
			{

				//60フレーム分、待つ
				if (cnt > 0)
				{
					--cnt;	//カウントアップ
				}
				else
				{
					FadeEnd = true;	//フェード終了
				}

				//フェードアウトの処理
				double ToukaPercent = cnt / (double)FADE_MAX_CNT;						//透過%を計算
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, ToukaPercent * TOUKA_MAX_VALUE);	//透過させる
				DrawGraph(x, y, Handle, TRUE);					//画像を描画
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);								//透過をやめる


			}


		}
		else 		//フェードアウト終了したら
		{
			IsDraw = false;	//描画しない
			cnt = FADE_MAX_CNT;				//カウントリセット
			IsFade = false;	//フェードアウトしない
		}

	}
	else		//フェードアウトしない時は
	{
		cnt = FADE_MAX_CNT;		//カウントリセット

		if (IsDraw)	//描画してよければ
		{
			DrawGraph(x, y, Handle, TRUE);	//画像を描画
		}

	}



	return;
}

//画像を描画（左右中央）
//引数：int：描画Y位置
void Image::DrawCenterX(int y)
{

	int x = 0;	//描画するY位置
	x = (GAME_WIDTH / 2) - (Width / 2);	//左右中央になるように計算

	static int cnt = FADE_MAX_CNT;				//カウント用

	if (IsFade)	//フェードアウトするときは
	{
		if (!FadeEnd)	//フェードアウト終了していなければ
		{

			if (IsDraw)	//描画してよければ
			{

				//60フレーム分、待つ
				if (cnt > 0)
				{
					--cnt;	//カウントアップ
				}
				else
				{
					FadeEnd = true;	//フェード終了
				}

				//フェードアウトの処理
				double ToukaPercent = cnt / (double)FADE_MAX_CNT;						//透過%を計算
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, ToukaPercent * TOUKA_MAX_VALUE);	//透過させる
				DrawGraph(x, y, Handle, TRUE);					//画像を描画
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);								//透過をやめる


			}


		}
		else 		//フェードアウト終了したら
		{
			IsDraw = false;	//描画しない
			cnt = FADE_MAX_CNT;				//カウントリセット
			IsFade = false;	//フェードアウトしない
		}

	}
	else		//フェードアウトしない時は
	{
		cnt = FADE_MAX_CNT;		//カウントリセット

		if (IsDraw)	//描画してよければ
		{
			DrawGraph(x, y, Handle, TRUE);	//画像を描画
		}

	}



	return;
}

//フェードアウトするか設定
void Image::SetIsFade(bool isfade)
{
	IsFade = isfade;
	FadeEnd = false;	//フェードアウト終了フラグリセット

	return;
}

//フェードエフェクトが終了しているか取得
bool Image::GetFadeEnd()
{
	return FadeEnd;
}
