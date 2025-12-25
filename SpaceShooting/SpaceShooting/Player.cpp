//Player.cpp

//########### ヘッダファイル読み込み #############
#include "Player.hpp"

//########### クラス定義 ############

//コンストラクタ
//引数：Image *：キャラクターの画像
Player::Player(Image* img)
{
	//メンバー初期化
	collision = { 0 };	//当たり判定
	Hp = 0;				//HP
	SpawnX = 0;			//弾発射地点X
	SpawnY = 0;			//弾発射地点Y

	this->img = img;
}

//デストラクタ
Player::~Player()
{
	for (auto b : bullet) { delete b; }
	vector<Bullet*> v;
	bullet.swap(v);

	delete img;	//img破棄
}

//毎回行う処理
void Player::UpDate()
{

	Move();		//プレイヤーの移動処理

	if (Mouse::OnRightClick())	//右クリックされたら
	{
		bullet.push_back(new Bullet());	//弾を生成
		bullet.back()->SetInit(SpawnX, SpawnY);	//初期設定
		bullet.back()->Shot();	//撃つ
	}

	//弾の処理
	for (int i = 0; i < bullet.size(); ++i)
	{
		bullet.at(i)->Move();	//弾の移動処理

		if (!bullet.at(i)->InScreen())	//画面外に出たら
		{
			delete bullet.at(i);	//破棄
			bullet.erase(bullet.begin() + i);
		}
	}

	Draw();	//プレイヤー描画
}


//初期設定
void Player::SetInit()
{
	img->SetInit();		//画像初期設定
	img->SetPos((GAME_WIDTH / 2) - (img->GetWidth() / 2), GAME_HEIGHT - img->GetHeight());	//描画位置設定
}

//初期化
void Player::Init()
{
	//当たり判定設定
	collision.left = (GAME_WIDTH / 2) - (img->GetWidth() / 2);		//左上X
	collision.top = GAME_HEIGHT - img->GetHeight();					//左上Y
	collision.right = collision.left + img->GetWidth();				//右下X
	collision.bottom = collision.top + img->GetHeight();			//右下Y

	//弾発射位置
	SpawnX = (collision.left + collision.right) / 2;
	SpawnY = collision.top;

	if (!bullet.empty())	//弾が発射されていたら
	{
		//弾を削除
		for (auto b : bullet)
		{
			delete b;
		}
		bullet.erase(bullet.begin(), bullet.end());	
	}

}

//描画
void Player::Draw()
{
	img->Draw(collision.left, collision.top);
	for (auto b : bullet) { b->Draw(); }		//弾描画
}

//移動処理
void Player::Move()
{
	int x = 0, y = 0;		//マウス位置取得用
	Mouse::GetPos(&x, &y);	//マウス位置取得

	if (x - img->GetWidth() / 2 < GAME_LEFT || x + img->GetWidth() / 2 > GAME_WIDTH)	//画面外の場合
		return;			//移動しない

	//当たり判定移動
	collision.left = x - img->GetWidth() / 2;
	collision.right = collision.left + img->GetWidth();
	//弾発射位置
	SpawnX = (collision.left + collision.right) / 2;

}

//当たり判定取得
RECT Player::GetCol()
{
	return collision;
}

//弾の当たり判定取得
RECT Player::GetBulletCol(int element)
{
	return bullet.at(element)->GetCol();
}

//現在の弾の数を取得
int Player::GetBulleMax()
{
	return Bullet::GetElementMax();
}

//敵に弾が当たった
void Player::HitBullet(int element)
{
	delete bullet.at(element);	//破棄
	bullet.erase(bullet.begin() + element);
}
