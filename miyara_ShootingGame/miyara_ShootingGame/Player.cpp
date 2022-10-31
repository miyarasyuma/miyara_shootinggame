#include "Player.h"
#include"StraightBullets.h"
#include"KeyManager.h"
#include "DxLib.h"

Player::Player(T_Location location) :CharaBase(location, 10.f, T_Location{2,2}),score(0),life(10)
{

	//BulletsBase** bullets
	bullets = new BulletsBase * [30];
	for (int i = 0; i < 30; i++)
	{
		bullets[i] = nullptr;
	}
}

void Player::Update()
{
	T_Location newLocation = GetLocation();
	//プレイヤー操作キー
	if (KeyManager::OnKeyPressed(KEY_INPUT_W))//上
	{
		newLocation.y -= speed.y;
	}

	if (KeyManager::OnKeyPressed(KEY_INPUT_A))//左
	{
		newLocation.x -= speed.x;
	}

	if (KeyManager::OnKeyPressed(KEY_INPUT_S))//下
	{
		newLocation.y += speed.y;
	}

	if (KeyManager::OnKeyPressed(KEY_INPUT_D))//右
	{
		newLocation.x += speed.x;
	}
	

	SetLocation(newLocation);

	int bulletCount;
	for (bulletCount = 0; bulletCount < 30; bulletCount++)
	{
		if (bullets[bulletCount] == nullptr)
		{
			break;
		}
		bullets[bulletCount]->Update();

		//画面外に行ったら弾を消す
		if (bullets[bulletCount]->isScreenOut())//画面外で消えたか確かめる
		{
			delete bullets[bulletCount];
			bullets[bulletCount] = nullptr;

			//配列を前に詰める
			if (bullets[bulletCount] == nullptr)
			{

			}
		}
	}

	if (KeyManager::OnMousePressed(MOUSE_INPUT_LEFT))
	{
		if (bulletCount < 30 && bullets[bulletCount] == nullptr)
		{
			bullets[bulletCount] = new StraightBullets(GetLocation());
		}
	}
}

void Player::Draw()
{
	DrawCircle(GetLocation().x, GetLocation().y, GetRadius(), GetColor(255, 0, 0));

	for (int bulletCount = 0; bulletCount < 30; bulletCount++)
	{
		if (bullets[bulletCount] == nullptr)
		{
			break;
		}
		bullets[bulletCount]->Draw();
	}
}

void Player::Hit()
{

}

bool Player::LifeCheck()
{
	bool ret = (life <= 0);
	return ret;
}

int  Player::GetScore()
{
	return score;
}