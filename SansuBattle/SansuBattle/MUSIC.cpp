//Music.cpp
//音楽用クラス

//################### ヘッダファイル読み込み ####################
#include "Music.hpp"

//################## クラス定義 ###########################

//コンストラクタ
//引　数：const char *：画像のディレクトリ
//引　数：const char *：画像の名前
Music::Music(const char *dir, const char *name)
{
	//メンバ変数を初期化
	FilePath = "";	//パス
	FileName = "";	//名前

	IsLoad = false;	//読み込めたか？

	//音を読み込み
	string LoadfilePath;	//音のファイルパスを作成
	LoadfilePath += dir;
	LoadfilePath += name;

	Handle = LoadSoundMem(LoadfilePath.c_str());	//音の読み込み

	if (Handle == -1)	//音が読み込めなかったとき
	{
		string ErroeMsg(MUSIC_ERROR_MSG);	//エラーメッセージ作成
		ErroeMsg += TEXT('\n');					//改行
		ErroeMsg += LoadfilePath;				//音のパス

		MessageBox(
			NULL,
			ErroeMsg.c_str(),	//char * を返す
			TEXT(MUSIC_ERROR_TITLE),
			MB_OK);

		return;
	}

	FilePath = LoadfilePath;		//音のパスを設定
	FileName = name;				//音の名前を設定

	PlayType = DX_PLAYTYPE_BACK;	//最初は再生方法をバックグラウンド再生にする

	IsLoad = true;				//読み込み成功

	IsPlayed = false;		//再生済みではない

}

//コンストラクタ
Music::Music()
{
	//メンバ変数を初期化
	FilePath = "";	//パス
	FileName = "";	//名前

	IsLoad = false;	//読み込めたか？

	Handle = -1;

	PlayType = DX_PLAYTYPE_BACK;	//最初は再生方法をバックグラウンド再生にする

	IsPlayed = false;		//再生済みではない

}

//デストラクタ
Music::~Music()
{
	DeleteMusicMem(Handle);		//音のハンドルの削除
}

//読み込み 
//引　数：const char *：画像のディレクトリ
//引　数：const char *：画像の名前
bool Music::Load(const char* dir, const char* name)
{

	//音を読み込み
	string LoadfilePath;	//音のファイルパスを作成
	LoadfilePath += dir;
	LoadfilePath += name;

	Handle = LoadSoundMem(LoadfilePath.c_str());	//音の読み込み

	if (Handle == -1)	//音が読み込めなかったとき
	{
		string ErroeMsg(MUSIC_ERROR_MSG);	//エラーメッセージ作成
		ErroeMsg += TEXT('\n');					//改行
		ErroeMsg += LoadfilePath;				//音のパス

		MessageBox(
			NULL,
			ErroeMsg.c_str(),	//char * を返す
			TEXT(MUSIC_ERROR_TITLE),
			MB_OK);

		return false;	//読み込み失敗
	}

	FilePath = LoadfilePath;		//音のパスを設定
	FileName = name;				//音の名前を設定

	PlayType = DX_PLAYTYPE_BACK;	//最初は再生方法をバックグラウンド再生にする

	IsPlayed = false;		//再生済みではない
	IsLoad = true;	//読み込み成功

	return true;	//読み込み成功

}

//読み込めたかどうかを取得
bool Music::GetIsLoad()
{
	return IsLoad;
}

//音が再生されているか取得
//戻り値：再生中：true　再生中じゃない：false
bool Music::GetIsPlay()
{
	return CheckSoundMem(Handle);
}

//初期設定
void Music::SetInit(int type, double volume)
{
	PlayType = type;		//再生方法設定
	ChengeVolume(volume);	//音量を設定
}

//再生方法を変更する
void Music::ChengePlayType(int type)
{
	PlayType = type;	
}

//音量を変更する
//引数：int：音量(0～100%で指定)
void Music::ChengeVolume(double volume)
{
	ChangeVolumeSoundMem(VOLUME_MAX * (volume / 100), Handle);
}

//音を再生する
void Music::Play(bool check)
{
	if (check)	//プレイ中か確認する場合
	{
		if (!GetIsPlay())		//プレイ中じゃなければ
		{
			PlaySoundMem(Handle, PlayType);	//音の再生
		}
	}
	else		//確認しない場合
	{
		PlaySoundMem(Handle, PlayType);	//音の再生
	}

}

//音を再生する(1回だけ)
void Music::PlayOne(bool check)
{
	if (!IsPlayed)		//再生済みじゃなければ
	{
		if (check)	//プレイ中か確認する場合
		{
			if (!GetIsPlay())		//プレイ中じゃなければ
			{
				PlaySoundMem(Handle, PlayType);	//音の再生

				IsPlayed = true;		//再生済み

			}

		}
		else		//確認しない場合
		{
			PlaySoundMem(Handle, PlayType);	//音の再生

			IsPlayed = true;		//再生済み
		}
	}
}

//再生済みかどうかをリセットする
void Music::Reset()
{
	IsPlayed = false;	//再生済みじゃない
}

//音を止める
void Music::Stop(void)
{
	StopSoundMem(Handle);		//音を止める
}
