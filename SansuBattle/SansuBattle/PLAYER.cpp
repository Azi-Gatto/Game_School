//Player.cpp
//プレイヤーを管理するクラス

//################### ヘッダファイル読み込み #####################
#include "Player.hpp"

//################### クラス定義 ##################

//コンストラクタ
Player::Player()
{
	hp_img->Load(IMG_DIR_PLAYER, IMG_NAME_HP);	//HP画像生成
	HP_X = 0;		//HP描画X位置
	HP_Y = 0;		//HP描画Y位置
	InputNum = 0;	//入力された値
	keydown = new KeyDown();	//キー入力用
	reverse = false;			//反転描画するか
}

//デストラクタ
Player::~Player()
{
	delete keydown;	//keydown破棄
}

//初期設定
bool Player::SetInit()
{
	if (!hp_img->GetIsLoad()) { return false; }	//読み込み失敗
	hp_img->SetInit();	//画像初期設定
	HP_X = GAME_WIDTH - hp_img->GetWidth();	//HP描画X位置
	HP_Y = PLAYER_HP_DRAW_Y;				//HP描画Y位置
	reverse = true;	//反転描画
	return true;	//読み込み成功
}

//*********************** キー入力関係 *********************************** 
//入力中の数字を描画する
void Player::DrawInputNum()
{

	string inp = std::to_string(InputNum);	//入力された数字を文字列に変換

	int Strlen = strlen(inp.c_str());													//文字列の長さを取得
	int Width = GetDrawStringWidthToHandle(inp.c_str(), Strlen, Font::GetNowHandle());	//横幅取得
	int Height = GetFontSizeToHandle(Font::GetNowHandle());								//高さ取得

	DrawFormatStringToHandle((GAME_WIDTH / 2) - (Width / 2), (GAME_HEIGHT / 2) - (Height / 2), COLOR_WHITE, Font::GetNowHandle(), "%s", inp.c_str());	//入力中の数字を描画

}

//キー入力中か確認
//戻り値：bool：true 入力終了：false 入力中
bool Player::CheckInputKey()
{
	keydown->KeyDownUpdate();			//キー入力更新
	int InputNumBuf = InputNum;			//現在の入力されている値を取得
	static int Weight = 10;				//桁の重み
	static int digit = 0;				//桁数
	int NewInputKey = GetInputKey();	//新たに入力されたキー

	if (INPUT_NUM_0 <= NewInputKey && NewInputKey <= INPUT_NUM_9)	//数値を入力した時
	{

		if (digit < INP_MAX_DIGIT)	//最大桁数より少ない場合は
		{
			//入力値に桁の重みを付けて計算
			//負の値の時は、マイナス、正の値の時は、プラスで、計算する
			InputNumBuf < 0 ? InputNumBuf = (InputNumBuf * Weight) - NewInputKey : InputNumBuf = (InputNumBuf * Weight) + NewInputKey;
			
			digit = std::to_string(InputNumBuf).length();	//桁数を計算

		}

	}
	else	//数値以外を入力した時
	{
		if (NewInputKey == INPUT_ENTER)	//決定された場合
		{
			InputNumBuf = 0;	//初期化
			digit = 0;			//桁数初期化
			return true;		//入力終了
		}

		if (NewInputKey == INPUT_BACK)	//バックスペースを押されたら
		{
			InputNumBuf /= Weight;		//一文字分消す
			digit = std::to_string(InputNumBuf).length();	//桁数を計算
		}

		if (NewInputKey == INPUT_MINUS)	//マイナスキーを押されたら
		{
			InputNumBuf *= -1;			//マイナスの値に変換
		}
	}

	InputNum = InputNumBuf;		//入力された数字を設定

	return false;
}

//入力リセット
void Player::InpReset()
{
	InputNum = 0;	//入力内容リセット
}

//入力されたキーを取得
int Player::GetInputKey()
{
	switch (keydown->GetInputKeyCode())		//入力されたキーコードごとに処理を分岐
	{

	case KEY_INPUT_0:		//0を入力された場合
	case KEY_INPUT_NUMPAD0:	//テンキーで0を入力された場合

		return INPUT_NUM_0;	//入力値0

		break;

	case KEY_INPUT_1:		//1を入力された場合
	case KEY_INPUT_NUMPAD1:	//テンキーで1を入力された場合

		return INPUT_NUM_1;	//入力値1

		break;

	case KEY_INPUT_2:		//2を入力された場合
	case KEY_INPUT_NUMPAD2:	//テンキーで2を入力された場合

		return INPUT_NUM_2;	//入力値2

		break;

	case KEY_INPUT_3:		//3を入力された場合
	case KEY_INPUT_NUMPAD3:	//テンキーで3を入力された場合

		return INPUT_NUM_3;	//入力値3

		break;

	case KEY_INPUT_4:		//4を入力された場合
	case KEY_INPUT_NUMPAD4:	//テンキーで4を入力された場合

		return INPUT_NUM_4;	//入力値4

		break;

	case KEY_INPUT_5:		//5を入力された場合
	case KEY_INPUT_NUMPAD5:	//テンキーで5を入力された場合

		return INPUT_NUM_5;	//入力値5

		break;

	case KEY_INPUT_6:		//6を入力された場合
	case KEY_INPUT_NUMPAD6:	//テンキーで6を入力された場合

		return INPUT_NUM_6;	//入力値6

		break;

	case KEY_INPUT_7:		//7を入力された場合
	case KEY_INPUT_NUMPAD7:	//テンキーで7を入力された場合

		return INPUT_NUM_7;	//入力値7

		break;

	case KEY_INPUT_8:		//8を入力された場合
	case KEY_INPUT_NUMPAD8:	//テンキーで8を入力された場合

		return INPUT_NUM_8;	//入力値8

		break;

	case KEY_INPUT_9:		//9を入力された場合
	case KEY_INPUT_NUMPAD9:	//テンキーで9を入力された場合

		return INPUT_NUM_9;	//入力値9

		break;

	case KEY_INPUT_RETURN:		//エンターキー（決定された）場合
	case KEY_INPUT_NUMPADENTER:	//テンキーでエンターキー（決定された）場合

		return INPUT_ENTER;		//決定

		break;

	case KEY_INPUT_BACK:		//バックスペースキーを押された場合

		return INPUT_BACK;		//バック

		break;

	case KEY_INPUT_MINUS:		//マイナスキー
	case KEY_INPUT_SUBTRACT:	//テンキーのマイナスキー

		return INPUT_MINUS;		//マイナス

		break;

	default:					//それ以外の場合（数字以外の入力の場合）

		return INPUT_NOT_NUM;	//数字以外の入力
		break;
	}
}

//入力された答えを取得
int Player::GetAns()
{
	return InputNum;
}
