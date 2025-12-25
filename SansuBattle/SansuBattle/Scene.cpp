//Scene.cpp

//############# ヘッダファイル読み込み ###############
#include "Scene.hpp"

//############## クラス定義 ################

int Scene::NowScene = 0;	//現在のシーン
bool Scene::GameEnd = false;//ゲームエンドフラグ
vector<Font*> Scene::font;	//フォント
vector<Data*> Scene::data;	//データ
int Scene::GameLevel = -1;	//ゲームレベル
int Scene::GameMode = -1;	//ゲームモード

//コンストラクタ
Scene::Scene()
{
	back = new Image();			//インスタンス生成
	bgm.push_back(new Music());	//インスタンス生成

	//フォント関係
	if (font.empty())	//フォントを作成していなかったら
	{
		font.push_back(new Font(FNAME_KOKUBAN, F_SIZE_NORMAL, F_BOLD_NORMAL, DX_FONTTYPE_ANTIALIASING));	//こくばんフォント（通常サイズ）作成
		font.push_back(new Font(FNAME_KOKUBAN, F_SIZE_MINI, F_BOLD_NORMAL, DX_FONTTYPE_ANTIALIASING));		//こくばんフォント（ミニサイズ）作成
		font.push_back(new Font(FNAME_KOKUBAN, F_SIZE_RANKING, F_BOLD_NORMAL, DX_FONTTYPE_ANTIALIASING));	//こくばんフォント（ランキングサイズ）作成
		font.push_back(new Font(FNAME_POP, F_SIZE_TIME, F_BOLD_NORMAL, DX_FONTTYPE_ANTIALIASING));			//ポップフォント（通常サイズ）作成
		for (auto f : font)
		{
			if (!f->GetIsCreate()) { IsLoad = false; return; }	//読み込み失敗
		}
	}

	start = false;		//Start処理を行ったか

	IsLoad = false;		//読み込めたか
}

//デストラクタ
Scene::~Scene()
{
	delete back;	//back破棄
	
	for (auto b : bgm) { delete b; }	//bgm破棄
	vector<Music*> v;
	v.swap(bgm);

	Font::ReleaseFont();	//読み込んだフォントを開放
}

//シーンが変わるごとに1回だけ行う処理
void Scene::Start()
{

}

//現在のシーンを取得
int Scene::GetNowScene()
{
	return NowScene;
}

//ゲームエンドフラグを取得
bool Scene::IsGameEnd()
{
	return GameEnd;
}

//フェードアウト処理
bool Scene::FadeOut()
{
	//フェードアウト処理
	static int cnt = 0;	//カウント用

	//60フレーム分、待つ
	if (cnt < FADE_MAX_CNT)
	{
		++cnt;	//カウントアップ
	}
	else	//60フレーム経過したら
	{
		cnt = 0;		//カウントリセット
		return true;	//フェードアウト終了
	}

	//フェードアウトの処理
	double ToukaPercent = cnt / (double)FADE_MAX_CNT;							//透過%を計算
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, ToukaPercent * TOUKA_MAX_VALUE);		//透過させる
	DrawBox(GAME_LEFT, GAME_TOP, GAME_WIDTH, GAME_HEIGHT, COLOR_BLACK, true);	//黒い四角を描画
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);									//透過をやめる

	return false;	//フェードアウト中

}
