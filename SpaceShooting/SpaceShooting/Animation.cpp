//Animation.cpp
//アニメーションを管理するクラス

//################ ヘッダファイル読み込み ##################
#include "Animation.hpp"

//################ クラス定義 ##############

vector<vector<int>> Animation::AnimList;	//読み込んだアニメーションリスト

//コンストラクタ
/*
引　数：int：アニメーションの種類
引　数：double：次の画像に変更する速さ
引　数：bool：アニメーションをループするかどうか
*/

Animation::Animation(int number, double changeSpeed, bool IsLoop)
{

	//アニメーションを読み込んで、リストを作成
	if (AnimList.empty())	//リスト未作成なら
	{
		IsLoad = CreateList();
		if (!IsLoad) { return; }	//読み込み失敗
	}

	//メンバー変数初期化
	IsLoad = false;			//読み込めたか？
	IsDrawEnd = false;		//描画終了したか?
	IsNowDraw = false;		//描画中か
	Width = 0;				//横幅を初期化
	Height = 0;				//高さを初期化

	Handle = AnimList.at(number);	//一覧から、指定された種類のアニメーションを取得

	ChangeMaxCnt = (GAME_FPS_SPEED * changeSpeed);
	ChangeCnt = 0;	//アニメーションするフレームのカウント

	NextChangeSpeed = changeSpeed;	//画像を変える速さ

	IsAnimeLoop = IsLoop;		//アニメーションがループするか

	Handle_itr = Handle.begin();	//先頭要素をイテレータに設定

	IsLoad = true;		//読み込めた

}

//デストラクタ
Animation::~Animation()
{

	//vectorのメモリ解放を行う
	vector<int> v;			//空のvectorを作成する
	Handle.swap(v);			//空と中身を入れ替える

}

//リスト作成
bool Animation::CreateList()
{
	vector<int> w;	//作業用
	string Path;	//path

	//***************************** 弾のアニメーション *****************************************
	w.resize(ANIM_BULLET_ALL_CNT);
	Path = ANIM_DIR;
	Path += ANIM_NAME_BULLET;

	//読み込み
	LoadDivGraph(Path.c_str(), ANIM_BULLET_ALL_CNT, ANIM_BULLET_YOKO_CNT, ANIM_BULLET_TATE_CNT, ANIM_BULLET_WIDTH, ANIM_BULLET_HEIGHT, &w.front());

	if (w.front() == -1)	//画像が読み込めなかったとき
	{
		string ErrorMsg(ANIMATION_ERROR_MSG);		//エラーメッセージ作成
		ErrorMsg += TEXT('\n');						//改行
		ErrorMsg += Path;							//画像のパス

		MessageBox(
			NULL,
			ErrorMsg.c_str(),	//char * を返す
			TEXT(ANIMATION_ERROR_TTILE),
			MB_OK);

		return false;//読み込み失敗
	}

	AnimList.push_back(w);	//ハンドルを保存

	//***************************** 爆発のアニメーション *****************************************
	w.resize(ANIM_EXPLOSION_ALL_CNT);
	Path = ANIM_DIR;
	Path += ANIM_NAME_EXPLOSION;

	//読み込み
	LoadDivGraph(Path.c_str(), ANIM_EXPLOSION_ALL_CNT, ANIM_EXPLOSION_YOKO_CNT, ANIM_EXPLOSION_TATE_CNT, ANIM_EXPLOSION_WIDTH, ANIM_EXPLOSION_HEIGHT, &w.front());

	if (w.front() == -1)	//画像が読み込めなかったとき
	{
		string ErrorMsg(ANIMATION_ERROR_MSG);		//エラーメッセージ作成
		ErrorMsg += TEXT('\n');						//改行
		ErrorMsg += Path;							//画像のパス

		MessageBox(
			NULL,
			ErrorMsg.c_str(),	//char * を返す
			TEXT(ANIMATION_ERROR_TTILE),
			MB_OK);

		return false;//読み込み失敗
	}

	AnimList.push_back(w);	//ハンドルを保存

	return true;	//読み込み成功

}

//リストのハンドルを削除
void Animation::DeleteHandle()
{
	//リストに読み込んだアニメーションのハンドルを削除
	for (auto a : AnimList)
	{
		DeleteGraph(a.front());	
	}
}

//初期設定
void Animation::SetInit()
{
	GetGraphSize(Handle.front(), &Width, &Height);		//サイズ取得
}

//幅を取得
int Animation::GetWidth()
{
	return Width;
}

//高さを取得
int Animation::GetHeight()
{
	return Height;
}

//読み込めた？
bool Animation::GetIsLoad(void)
{
	return IsLoad;
}

//描画終了したかどうか取得
bool Animation::GetIsDrawEnd()
{
	return IsDrawEnd;
}

//描画中か取得
bool Animation::GetIsNowDraw()
{
	return IsNowDraw;
}

//リセット
void Animation::Reset()
{
	IsDrawEnd = false;
	IsNowDraw = false;		//描画中か
}

//描画
/*
引数：int：Xの描画位置
引数：int：Yの描画位置
*/
void Animation::Draw(int x, int y)
{
	if (IsDrawEnd == false)	//アニメーションが終わっていなければ
	{
		IsNowDraw = true;		//描画中か
		DrawGraph(x, y, *Handle_itr, TRUE);	//イテレータ(ポインタ)を使用して描画
	}

	if (ChangeCnt == ChangeMaxCnt)	//次の画像を表示する時がきたら
	{
		//this->Handle.end()は、最後の要素の１個次のイテレータを返すので、-1している。
		if (Handle_itr == Handle.end() - 1)	//イテレータ(ポインタ)が最後の要素のときは
		{
			//アニメーションをループしないなら
			if (IsAnimeLoop == false)
			{
				IsDrawEnd = true;	//描画終了
				IsNowDraw = false;	//描画中か
			}

			//次回の描画に備えて、先頭の画像に戻しておく
			Handle_itr = Handle.begin();	//イテレータ(ポインタ)を要素の最初に戻す
		}
		else
		{
			++Handle_itr;	//次のイテレータ(ポインタ)(次の画像)に移動する
		}

		ChangeCnt = 0;	//カウント初期化
	}
	else
	{
		++ChangeCnt;	//カウントアップ
	}

}

//画面中央に描画
void Animation::DrawCenter()
{
	if (IsDrawEnd == false)	//アニメーションが終わっていなければ
	{
		IsNowDraw = true;		//描画中か
		DrawGraph((GAME_WIDTH / 2) - (Width / 2), (GAME_HEIGHT / 2) - (Height / 2), *Handle_itr, TRUE);	//イテレータ(ポインタ)を使用して描画
	}

	if (ChangeCnt == ChangeMaxCnt)	//次の画像を表示する時がきたら
	{
		//this->Handle.end()は、最後の要素の１個次のイテレータを返すので、-1している。
		if (Handle_itr == Handle.end() - 1)	//イテレータ(ポインタ)が最後の要素のときは
		{
			//アニメーションをループしないなら
			if (IsAnimeLoop == false)
			{
				IsNowDraw = false;	//描画中か
				IsDrawEnd = true;	//描画終了
			}

			//次回の描画に備えて、先頭の画像に戻しておく
			Handle_itr = Handle.begin();	//イテレータ(ポインタ)を要素の最初に戻す
		}
		else
		{
			++Handle_itr;	//次のイテレータ(ポインタ)(次の画像)に移動する
		}

		ChangeCnt = 0;	//カウント初期化
	}
	else
	{
		++ChangeCnt;	//カウントアップ
	}

}

//指定された領域内の中央に描画
void Animation::DrawCenter(RECT rect)
{

	int rect_center_x = rect.left + ((rect.right - rect.left) / 2);	//領域の中央X位置を計算
	int rect_center_y = rect.top + ((rect.bottom - rect.top) / 2);	//領域の中央Y位置を計算
	int x = rect_center_x - (Width / 2);				//描画位置Xを計算
	int y = rect_center_y - (Height / 2);				//描画位置Yを計算

	if (IsDrawEnd == false)	//アニメーションが終わっていなければ
	{
		IsNowDraw = true;		//描画中か
		DrawGraph(x, y, *Handle_itr, TRUE);	//イテレータ(ポインタ)を使用して描画
	}

	if (ChangeCnt == ChangeMaxCnt)	//次の画像を表示する時がきたら
	{
		//this->Handle.end()は、最後の要素の１個次のイテレータを返すので、-1している。
		if (Handle_itr == Handle.end() - 1)	//イテレータ(ポインタ)が最後の要素のときは
		{
			//アニメーションをループしないなら
			if (IsAnimeLoop == false)
			{
				IsDrawEnd = true;	//描画終了
				IsNowDraw = false;	//描画中か
			}

			//次回の描画に備えて、先頭の画像に戻しておく
			Handle_itr = Handle.begin();	//イテレータ(ポインタ)を要素の最初に戻す
		}
		else
		{
			++Handle_itr;	//次のイテレータ(ポインタ)(次の画像)に移動する
		}

		ChangeCnt = 0;	//カウント初期化
	}
	else
	{
		++ChangeCnt;	//カウントアップ
	}

}
