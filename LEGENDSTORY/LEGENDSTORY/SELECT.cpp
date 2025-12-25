//SELECT.cpp
//選択肢を管理するクラス


//###################### ヘッダファイル読み込み ######################
#include "SELECT.hpp"

//###################### クラス定義 ##########################

IMAGE* SELECT::image_ui;	//インストラクタ生成

//コンストラクタのオーバーロード
/*
選択肢の内容を設定せずにオブジェクトの生成のみを行う
*/
SELECT::SELECT()
{

	if (this->image_ui == NULL)	//UI画像を生成していなければ
	{
		this->image_ui = new IMAGE(SELECT_DIR, SELECT_TRIANGLENAME);		//UI画像生成
		this->image_ui->AddImage(SELECT_DIR, SELECT_TRIANGLE_MINI_NAME);	//UI画像追加
	}


	this->IsKeyOpe = true;			//キー操作可能
	this->SelectFlg = false;		//選択されていない
	this->IsDrawImage = true;		//UI画像を描画してよい
	this->Side_Mode = false;		//横向きに選択肢を並べない
	this->BackFlg = false;			//戻る選択はされていない
	this->IsScroll = false;			//スクロールしていない
	this->ScrollCnt = 0;			//スクロール量初期化

	this->DefIsKeyOpe = true;		//デフォルトはキー操作可能
	this->DefIsDrawImage = true;	//デフォルトはUI表示

	return;

}

//デストラクタ
SELECT::~SELECT()
{

	//delete this->image_ui;	//UI画像破棄

	//vectorのメモリ解放を行う
	std::vector<std::string> v;			//空のvectorを作成する
	this->Str.swap(v);					//空と中身を入れ替える

	//vectorのメモリ解放を行う
	std::vector<int> v2;			//空のvectorを作成する
	this->Code.swap(v2);			//空と中身を入れ替える

	return;

}

//選択肢のキー操作
/*
引数：KEYDOWN *：キー操作
引数：MUSIC *  ：SE再生用
*/
void SELECT::SelectOperation(KEYDOWN *keydown,MUSIC *se)
{

	if (this->IsKeyOpe)		//キー操作可能なら
	{

		if (this->Side_Mode)	//横向きに選択肢が並んでいる場合は
		{
			//A、Dキーで操作
			if (keydown->IsKeyDownOne(KEY_INPUT_A))		//Aキーを押されたら
			{
				if (this->Str_itr != this->Str.begin())	//最初の要素を選択していなければ
				{
					//SEの再生
					se->Play((int)SYS_SE_CURSOR);					//カーソル移動のSEを鳴らす
					--this->Str_itr;		//前の要素へ

				}
			}
			else if (keydown->IsKeyDownOne(KEY_INPUT_D))	//Dキーを押されたら
			{
				if (this->Str_itr != this->Str.end() - 1)	//最後の要素を選択していなければ
				{
					//SEの再生
					se->Play((int)SYS_SE_CURSOR);					//カーソル移動のSEを鳴らす
					++this->Str_itr;		//次の要素へ
				}
			}


		}
		else					//縦向きに選択肢が並んでいる場合は
		{
			//W、Sキーで操作
			if (keydown->IsKeyDownOne(KEY_INPUT_W))		//Wキーを押されたら
			{
				if (this->Str_itr != this->Str.begin())	//最初の要素を選択していなければ
				{
					//SEの再生
					se->Play((int)SYS_SE_CURSOR);					//カーソル移動のSEを鳴らす
					--this->Str_itr;		//前の要素へ

				}
			}
			else if (keydown->IsKeyDownOne(KEY_INPUT_S))	//Sキーを押されたら
			{
				if (this->Str_itr != this->Str.end() - 1)	//最後の要素を選択していなければ
				{
					//SEの再生
					se->Play((int)SYS_SE_CURSOR);					//カーソル移動のSEを鳴らす
					++this->Str_itr;		//次の要素へ
				}
			}

		}

		if (keydown->IsKeyDownOne(KEY_INPUT_RETURN))	//エンターキーを押されたら
		{
			//SEの再生
			se->Play((int)SYS_SE_KETTEI);		//決定の効果音を鳴らす
			keydown->KeyDownUpdate();			//キー入力の状態をリセット

			this->SelectFlg = true;				//選択された

		}
		else if (keydown->IsKeyDownOne(KEY_INPUT_BACK))	//バックスペースキーを押されたら
		{
			//SEの再生
			se->Play((int)SYS_SE_CANSEL);		//キャンセルの効果音を鳴らす
			keydown->KeyDownUpdate();			//キー入力の状態をリセット

			this->BackFlg = true;				//戻る選択をした
		}

	}

	return;

}

//選択した要素の要素番号を取得する
int SELECT::GetSelectNum(void)
{
	for (int i = 0; i < this->Str.size(); ++i)
	{
		if (*this->Str_itr == this->Str[i])		//選択している要素番号と、一致したら
		{
			return i;		//現在の要素番号を返す
		}
	}
}

//選択肢の内容を消去
void SELECT::SelectClear()
{
	this->Str.clear();
	this->Str_itr = this->Str.begin();
	this->Code.clear();
	return;
}

//現在選択中の要素を最初に戻す
void SELECT::NowSelectReset(void)
{
	this->Str_itr = this->Str.begin();
	return;
}

//選択肢の内容を描画する
/*
引数：int：描画X位置
引数：int：描画Y位置
引数：int：描画するUI画像の種類
引数：unsigned int：描画色:デフォルトは白色
引数：int：横向きに選択肢を並べるときの描画間隔

*/
void SELECT::Draw(int x, int y,int kind,unsigned int color,int side_select)
{

	//***************************** サイズ取得処理 *******************************
	int Height = 0;		//高さ取得
	int Strlen = 0;		//文字列の長さ取得用
	int MaxStrlen = 0;	//最も長い文字列の長さ
	int Width = 0;		//文字列の幅取得用
	std::string MaxStr;	//最も長い文字列

	MaxStr = this->Str[0].c_str();	//最も長い文字列に最初の文字列をセット

	for (int i = 0; i < (int)this->Str.size(); i++)
	{
		Strlen = strlen(this->Str[i].c_str());	//文字列の長さ取得

		if (MaxStrlen < Strlen)	//最大文字列よりも長ければ
		{
			MaxStrlen = Strlen;	//最大文字列を更新
			MaxStr = this->Str[i].c_str();	//最大文字列を更

		}

	}

	
	Width = GetDrawStringWidth(MaxStr.c_str(), MaxStrlen);	//横幅取得

	Height = GetFontSize();		//高さ取得

	if (this->Side_Mode)		//横向きに選択肢を並べている場合
	{
		//******************************** 描画処理 ***************************************
		for (int i = 0; i < this->Str.size(); ++i)
		{
			if (*this->Str_itr == this->Str[i])			//選択中の要素だったら
			{

				if (this->IsDrawImage)	//表示してよければ
				{
					if (kind == (int)SELECT_TRIANGLE)	//通常サイズの場合
					{
						this->image_ui->Draw((x + i * side_select), y + IMAGE_SPACE, kind);		//横向き三角描画
					}
					else							//ミニサイズの場合
					{
						this->image_ui->Draw((x + i * side_select), y + IMAGE_MINI_SPACE, kind);	//横向き三角描画
					}

				}

				DrawFormatString((x + i * side_select) + this->image_ui->GetWidth(kind), y, color, "%s", this->Str[i].c_str());	//選択肢描画
			}
			else
			{
				DrawFormatString((x + i * side_select) + this->image_ui->GetWidth(kind), y, color, "%s", this->Str[i].c_str());	//選択肢描画
			}
		}

	}
	else						//立て向きに選択肢を並んでいる場合
	{

		for (int i = 0; i < this->Str.size(); ++i)
		{
			if (*this->Str_itr == this->Str[i])			//選択中の要素だったら
			{
				if (this->IsDrawImage)		//表示してよければ
				{
					if (kind == (int)SELECT_TRIANGLE)	//通常サイズの場合
					{
						this->image_ui->Draw(x, y + i * Height + IMAGE_SPACE, kind);		//横向き三角描画
					}
					else							//ミニサイズの場合
					{
						this->image_ui->Draw(x, y + i * Height + IMAGE_MINI_SPACE, kind);	//横向き三角描画
					}
				}


				DrawFormatString(x + this->image_ui->GetWidth(kind), y + i * Height, color, "%s", this->Str[i].c_str());	//選択肢描画
			}
			else
			{
				DrawFormatString(x + this->image_ui->GetWidth(kind), y + i * Height, color, "%s", this->Str[i].c_str());	//選択肢描画
			}
		}


	}


}

//選択肢の内容を中央に描画する
/*
引数：int：描画X位置
引数：int：描画Y位置
引数：int：描画するUI画像の種類
引数：unsigned int：描画色:デフォルトは白色
*/
void SELECT::DrawCenter(int x, int y,int kind, unsigned int color)
{

	int Height = 0;		//高さ取得
	int Strlen = 0;		//文字列の長さ取得用
	int MaxStrlen = 0;	//最も長い文字列の長さ
	int Width = 0;		//文字列の幅取得用
	std::string MaxStr;	//最も長い文字列

	MaxStr = this->Str[0].c_str();	//最も長い文字列に最初の文字列をセット

	for (int i = 0; i < (int)this->Str.size(); i++)
	{
		Strlen = strlen(this->Str[i].c_str());	//文字列の長さ取得

		if (MaxStrlen < Strlen)	//最大文字列よりも長ければ
		{
			MaxStrlen = Strlen;	//最大文字列を更新
			MaxStr = this->Str[i].c_str();	//最大文字列を更

		}

	}

	Width = GetDrawStringWidth(MaxStr.c_str(), MaxStrlen);	//横幅取得

	x -= (Width / 2);	//文字の幅の半分を引いて、真ん中に描画する

	Height = GetFontSize();	//高さ取得

	for (int i = 0; i < this->Str.size(); ++i)
	{
		if (*this->Str_itr == this->Str[i])			//選択中の要素だったら
		{

			if (kind == (int)SELECT_TRIANGLE)	//通常サイズの場合
			{
				this->image_ui->Draw(x , y + i * Height + IMAGE_SPACE, kind);		//横向き三角描画
			}
			else							//ミニサイズの場合
			{
				this->image_ui->Draw(x, y + i * Height + IMAGE_MINI_SPACE, kind);	//横向き三角描画
			}

			DrawFormatString(x + this->image_ui->GetWidth(kind), y + i * Height, color, "%s", this->Str[i].c_str());	//選択肢描画
		}
		else
		{
			DrawFormatString(x + this->image_ui->GetWidth(kind), y + i * Height, color, "%s", this->Str[i].c_str());	//選択肢描画
		}
	}

}

//選択肢の内容をスクロール描画する(立て向きに並んでいる場合のみ使用可能)
/*
引数：int：描画X位置
引数：int：描画Y位置
引数：int：Y位置から描画する高さ
引数：int：描画するUI画像の種類
引数：unsigned int：描画色:デフォルトは白色
引数：int：横向きに選択肢を並べるときの描画間隔
*/
void SELECT::DrawScroll(int x, int y, int rectheight, int kind, unsigned int color, int side_select)
{

	//***************************** サイズ取得処理 *******************************
	int Height = 0;		//高さ取得
	int Strlen = 0;		//文字列の長さ取得用
	int MaxStrlen = 0;	//最も長い文字列の長さ
	int Width = 0;		//文字列の幅取得用
	std::string MaxStr;	//最も長い文字列

	MaxStr = this->Str[0].c_str();	//最も長い文字列に最初の文字列をセット

	for (int i = 0; i < (int)this->Str.size(); i++)
	{
		Strlen = strlen(this->Str[i].c_str());	//文字列の長さ取得

		if (MaxStrlen < Strlen)	//最大文字列よりも長ければ
		{
			MaxStrlen = Strlen;	//最大文字列を更新
			MaxStr = this->Str[i].c_str();	//最大文字列を更

		}

	}

	Width = GetDrawStringWidth(MaxStr.c_str(), MaxStrlen);	//横幅取得
	Height = GetFontSize();		//高さ取得

	//スクロールし始める位置を計算する
	int scroll_start = 0;		//スクロールをスタートし始める場所
	this->DrawTotalHeight = 0;	//描画範囲内の選択肢をすべて合わせたときの高さ初期化

	while (true)	//無限ループ
	{
		if (this->DrawTotalHeight + Height < rectheight)	//スクロールせずに描画できる範囲内だったら
		{
			this->DrawTotalHeight += Height;	//高さを加算
			++scroll_start;			//スクロール開始位置を加算
		}
		else	//スクロールせずに描画できる範囲を超えたら
		{
			this->DrawTotalHeight -= Height;	//スクロール開始位置は、描画範囲を超える前のため、超えてしまった分、高さを引く
			--scroll_start;			//スクロール開始位置は、描画範囲を超える前のため、1個ぶんマイナスする
			break;	//ループを抜ける
		}
	}

	//スクロールするか設定
	if (this->GetSelectNum() < scroll_start)	//スクロール開始地点を超えていなければ
	{
		this->IsScroll = false;	//スクロールしていない
	}
	else		//選択中の要素がスクロール開始地点を超えたら
	{
		this->IsScroll = true;	//スクロール開始
	}

	//スクロール量設定
	this->ScrollCnt = this->GetSelectNum() - scroll_start;	//選択肢をスクロールした数
	if (this->ScrollCnt < 0)	//スクロールしていない時は
	{
		this->ScrollCnt = 0;	//スクロール量を0に設定
	}

	//描画処理
	for (int i = 0; i < this->Str.size(); ++i)
	{

		if (!this->IsScroll)	//スクロール開始していなければ
		{
			//スクロールせずに描画
			if (y + i * Height <= y + this->DrawTotalHeight)	//描画範囲内なら
			{
				if (i == this->GetSelectNum())	//選択中の要素だったら
				{
					if (this->IsDrawImage)		//表示してよければ
					{
						if (kind == (int)SELECT_TRIANGLE)	//通常サイズの場合
						{
							this->image_ui->Draw(x, y + i * Height + IMAGE_SPACE, kind);		//横向き三角描画
						}
						else							//ミニサイズの場合
						{
							this->image_ui->Draw(x, y + i * Height + IMAGE_MINI_SPACE, kind);	//横向き三角描画
						}
					}

					DrawFormatString(x + this->image_ui->GetWidth(kind), y + i * Height, color, "%s", this->Str[i].c_str());	//選択肢描画
				}
				else
				{
					DrawFormatString(x + this->image_ui->GetWidth(kind), y + i * Height, color, "%s", this->Str[i].c_str());	//選択肢描画
				}

			}
		}
		else	//スクロール開始していたら
		{

			//スクロール描画
			if (y + ((i - this->ScrollCnt) * Height) <= y + this->DrawTotalHeight &&
				y + ((i - this->ScrollCnt) * Height) >= y)		//描画範囲内なら
			{
				//選択中の要素を指す、横向き三角の画像を固定して描画
				if (this->IsDrawImage)		//表示してよければ
				{
					if (kind == (int)SELECT_TRIANGLE)	//通常サイズの場合
					{
						this->image_ui->Draw(x, y + this->DrawTotalHeight + IMAGE_SPACE, kind);		//横向き三角描画
					}
					else							//ミニサイズの場合
					{
						this->image_ui->Draw(x, y + this->DrawTotalHeight + IMAGE_MINI_SPACE, kind);	//横向き三角描画
					}

					DrawFormatString(x + this->image_ui->GetWidth(kind), y + ((i - this->ScrollCnt) * Height), color, "%s", this->Str[i].c_str());	//選択肢描画

				}
				else
				{
					DrawFormatString(x + this->image_ui->GetWidth(kind), y + ((i - this->ScrollCnt) * Height), color, "%s", this->Str[i].c_str());	//選択肢描画
				}

			}

		}

	}

}

//画像サイズを設定
void SELECT::SetSize(void)
{
	this->image_ui->SetSize();	//イメージ画像のサイズ設定

	return;
}

//選択肢の内容を追加
/*
引数：const char *：追加する文字列
引数：int	:コード番号がある場合はコード番号を設定する
*/
void SELECT::AddSelect(const char *str,int code)
{
	this->Str.push_back(str);	//選択肢追加
	this->Str_itr = this->Str.begin();	//最初の要素を選択状態へ
	this->Code.push_back(code);			//コード番号追加
	return;
}

//キー操作可能か設定
void SELECT::SetIsKeyOpe(bool iskeyope)
{
	this->IsKeyOpe = iskeyope;
	return;
}

//キー操作可能か取得
bool SELECT::GetIsKeyOpe(void)
{
	return this->IsKeyOpe;
}

//選択したか設定
void SELECT::SetSelectFlg(bool selectflg)
{
	this->SelectFlg = selectflg;
	return;
}

//選択したか取得
bool SELECT::GetSelectFlg(void)
{
	return this->SelectFlg;
}

//UI画像を描画してよいか設定
void SELECT::SetIsDrawImage(bool isdraw)
{
	this->IsDrawImage = isdraw;
	return;
}

//UI画像を描画してよいか取得
bool SELECT::GetIsDrawImage(void)
{
	return this->IsDrawImage;
}

//選択肢を横向きに並べるか設定
void SELECT::SetSideMode(bool side)
{
	this->Side_Mode = side;
	return;
}

//選択肢を横向きに並べるか取得
bool SELECT::GetSideMode(void)
{
	return this->Side_Mode;
}

//デフォルトの状態を設定
void SELECT::ChengeDefault(bool defiskey, bool defisdraw)
{
	this->DefIsKeyOpe = defiskey;		//キー操作可能か、デフォルト値
	this->DefIsDrawImage = defisdraw;	//UI画像描画してよいか、デフォルト値
	return;
}

//デフォルトの値に戻す
void SELECT::Default(void)
{
	this->IsKeyOpe = this->DefIsKeyOpe;			//キー操作をデフォルトの状態へ
	this->IsDrawImage = this->DefIsDrawImage;	//UI表示をデフォルトの状態へ
	this->SelectFlg = false;					//選択していない
	this->BackFlg = false;						//戻すかどうかをリセット
	this->NowSelectReset();						//現在の選択をリセット
	return;
}

//戻るを選択したか設定
void SELECT::SetBackFlg(bool back_flg)
{
	this->BackFlg = back_flg;	
	return;
}

//戻る選択をしたか取得
bool SELECT::GetBackFlg(void)
{
	return this->BackFlg;
}

//指定された要素に空白を入れる
void SELECT::InsertSpace(int element)
{
	this->Str[element] += " ";	//空白を追加
	return;
}

//指定された要素の文字列に文字を加える
void SELECT::AddText(int element, std::string add_text)
{
	this->Str[element] += add_text;
	return;
}

//選択肢の数を取得
int SELECT::GetSelectKind(void)
{
	return this->Str.size();
}

//選ばれた選択肢のコード番号を取得する
int SELECT::GetSelectCode(void)
{
	return this->Code[this->GetSelectNum()];	//選ばれた選択肢のコード番号を取得
}

//選択した内容を取得する
const char * SELECT::GetSelectText(void)
{
	return this->Str_itr->c_str();
}

//スクロールしているか取得
int SELECT::GetIsScroll(void)
{
	return this->IsScroll;
}

//スクロールした量を取得
int SELECT::GetScrollCnt(void)
{
	return this->ScrollCnt;
}

//描画範囲内の総合の高さを取得
int SELECT::GetDrawTotalHeight(void)
{
	return this->DrawTotalHeight;
}
