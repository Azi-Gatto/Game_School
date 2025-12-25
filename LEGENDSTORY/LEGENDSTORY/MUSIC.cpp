//MUSIC.cpp
//音楽用クラス

//################### ヘッダファイル読み込み ####################
#include "MUSIC.hpp"

//################## クラス定義 ###########################

//コンストラクタ
//引　数：const char *：画像のディレクトリ
//引　数：const char *：画像の名前
//引　数：int：音素材の種類数
MUSIC::MUSIC(const char *dir, const char *name)
{
	//メンバ変数を初期化
	this->FilePath = "";	//パス
	this->FileName = "";	//名前

	this->IsLoad = false;	//読み込めたか？

	//音を読み込み
	std::string LoadfilePath;	//音のファイルパスを作成
	LoadfilePath += dir;
	LoadfilePath += name;

	this->Handle.push_back(LoadSoundMem(LoadfilePath.c_str()));	//音の読み込み

	if (this->Handle.back() == -1)	//音が読み込めなかったとき
	{
		std::string ErroeMsg(MUSIC_ERROR_MSG);	//エラーメッセージ作成
		ErroeMsg += TEXT('\n');					//改行
		ErroeMsg += LoadfilePath;				//音のパス

		MessageBox(
			NULL,
			ErroeMsg.c_str(),	//char * を返す
			TEXT(MUSIC_ERROR_TITLE),
			MB_OK);

		return;
	}

	this->FilePath = LoadfilePath;		//音のパスを設定
	this->FileName = name;				//音の名前を設定

	this->PlayType = DX_PLAYTYPE_LOOP;	//最初は再生方法をループ再生にする

	this->IsLoad = true;				//読み込み成功

	this->IsPlay.push_back(false);		//再生中ではない
	this->IsPlayed.push_back(false);	//再生済みではない

	return;

}

//デストラクタ
MUSIC::~MUSIC()
{

	//範囲ベースの for ループ
	//vectorなどのコンテナクラスで使用できる
	//auto：型推論：コンパイラが初期値から推論して型を決めてくれる
	for (int handle : this->Handle)
	{
		DeleteMusicMem(handle);		//音のハンドルの削除
	}

	//vectorのメモリ解放を行う
	std::vector<int> v;			//空のvectorを作成する
	this->Handle.swap(v);		//空と中身を入れ替える

	//vectorのメモリ解放を行う
	std::vector<bool> v2;		//空のvectorを作成する
	this->IsPlay.swap(v2);		//空と中身を入れ替える

	//vectorのメモリ解放を行う
	std::vector<bool> v3;		//空のvectorを作成する
	this->IsPlayed.swap(v3);		//空と中身を入れ替える

	return;
}

//読み込めたかどうかを取得
bool MUSIC::GetIsLoad()
{
	return this->IsLoad;
}

//音が再生されているか取得
//戻り値：再生中：true　再生中じゃない：false
bool MUSIC::GetIsPlay(int kind)
{
	if (CheckSoundMem(this->Handle[kind]) == 1)	//再生中なら
	{
		this->IsPlay[kind] = true;	//再生中
	}
	else									//再生中じゃなければ
	{
		this->IsPlay[kind] = false;	//再生中じゃない
	}
	return this->IsPlay[kind];
}

//再生方法を変更する
void MUSIC::ChengePlayType(int type)
{
	this->PlayType = type;	
	return;
}

//音量を変更する
void MUSIC::ChengeVolume(int volume,int kind)
{
	ChangeVolumeSoundMem(volume, this->Handle[kind]);
	return;
}

//音を再生する
void MUSIC::Play(int kind)
{
	PlaySoundMem(this->Handle[kind], this->PlayType);	//音の再生
	return;
}

//音を止める（すべて）
void MUSIC::Stop(void)
{
	for (int i = 0; i < this->Handle.size(); ++i)
	{
		StopSoundMem(this->Handle[i]);		//音を止める
	}
	return;
}

//音を止める（指定されたものだけ）
void MUSIC::Stop(int kind)
{
	StopSoundMem(this->Handle[kind]);
	return;
}

//音を追加する
bool MUSIC::Add(const char *dir, const char *name)
{

	//音を読み込み
	std::string LoadfilePath;	//音のファイルパスを作成
	LoadfilePath += dir;
	LoadfilePath += name;

	this->Handle.push_back(LoadSoundMem(LoadfilePath.c_str()));	//音の読み込み

	if (this->Handle.back() == -1)	//音が読み込めなかったとき
	{
		std::string ErroeMsg(MUSIC_ERROR_MSG);	//エラーメッセージ作成
		ErroeMsg += TEXT('\n');					//改行
		ErroeMsg += LoadfilePath;				//音のパス

		MessageBox(
			NULL,
			ErroeMsg.c_str(),	//char * を返す
			TEXT(MUSIC_ERROR_TITLE),
			MB_OK);

		return false;	//読み込み失敗
	}

	this->IsPlay.push_back(false);		//再生中ではない
	this->IsPlayed.push_back(false);	//再生済みではない

	return true;		//読み込み成功

}

//再生済みか設定
void MUSIC::SetIsPlayed(int kind,bool Isplayed)
{
	this->IsPlayed[kind] = Isplayed;
	return;
}

//再生済みか取得
bool MUSIC::GetIsPlayed(int kind)
{
	return this->IsPlayed[kind];
}

//再生状態リセット
void MUSIC::Reset(void)
{

	for (int i = 0; i < this->IsPlayed.size(); ++i)	//全ての要素
	{
		this->IsPlayed[i] = false;	//再生済みではない
	}

	return;
}
