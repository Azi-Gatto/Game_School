//Effect.cpp
//エフェクトクラス

//################## ヘッダファイル読み込み ##################
#include "Effect.hpp"

//################## クラス定義 #######################

//コンストラクタ
//引数:Animation* :アニメーション
//引数:Music* :効果音
Effect::Effect(Animation* anim,Music* se)
{
	//メンバー初期化
	IsFadein = false;	//フェードインするか
	IsFadeout = false;	//フェードアウトするか

	this->anim = anim;	//アニメーション
	this->se = se;		//効果音
}

//コンストラクタ
Effect::Effect()
{
	//メンバー初期化
	IsFadein = false;	//フェードインするか
	IsFadeout = false;	//フェードアウトするか
}

//デストラクタ
Effect::~Effect()
{

	delete anim;	//anim破棄
	delete se;		//se破棄

}

//エフェクトを設定
//引数:Animation* :アニメーション
//引数:Music* :効果音
void Effect::SetEffect(Animation* anim,Music* se)
{
	this->anim = anim;
	this->se = se;
}

//描画
/*
引数：int：Xの描画位置
引数：int：Yの描画位置
*/
void Effect::Draw(int x, int y)
{
	anim->Draw(x, y);	//アニメーション描画
	se->PlayOne(false);	//効果音再生
}

//画面中央に描画
void Effect::DrawCenter()
{
	anim->DrawCenter();	//アニメーション描画
	se->PlayOne(false);	//効果音再生
}

//指定された領域内の中央に描画
void Effect::DrawCenter(RECT rect)
{
	anim->DrawCenter(rect);	//アニメーション描画
	se->PlayOne(false);	//効果音再生
}

//初期設定
void Effect::SetInit(void)
{
	anim->SetInit();	//アニメーション初期設定
	se->SetInit(DX_PLAYTYPE_BACK, 60);		//初期設定
}

//エフェクト終了したか取得
bool Effect::GetIsEffectEnd()
{
	return anim->GetIsDrawEnd();
}

//エフェクト描画中か取得
bool Effect::GetIsNowEffect()
{
	return anim->GetIsNowDraw();
}

//リセット
void Effect::Reset()
{
	anim->Reset();	//アニメーションリセット
	se->Reset();//効果音リセット
}
