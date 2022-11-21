#include"DxLib.h"
#include"StraightBullets.h"
#include "Enemy.h"

Enemy::Enemy(T_Location location) :CharaBase(location, 20.f, T_Location{0,0.5}),hp(10),point(10)
{
	bullets = new BulletsBase * [30];
	for (int i = 0; i < 30; i++)
	{
		bullets[i] = nullptr;
	}
}

void Enemy::Update()
{
	T_Location newLocation = GetLocation();
	newLocation.y += speed.y; 
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
			DeleteBullet(bulletCount);
			bulletCount--;
		}
	}
	if (bulletCount < 30 && bullets[bulletCount] == nullptr)
	{
		bullets[bulletCount] = new StraightBullets(GetLocation(), T_Location{ 0,2 });
	}
}

void Enemy::Draw()
{
	DrawCircle(GetLocation().x, GetLocation().y, GetRadius(), GetColor(0, 0, 255));//敵の本体

	for (int bulletCount = 0; bulletCount < 30; bulletCount++)
	{
		if (bullets[bulletCount] == nullptr)
		{
			break;
		}
		bullets[bulletCount]->Draw();
	}
}

void Enemy::Hit(int damage)//Enemy
{
	if (0 < damage)
	{
		hp -= damage;
		if (hp < 0)
		{
			hp = 0;
		}
	}
}

bool Enemy::HpCheck()//Enemyの体力	
{
	//０になったらtrue,0以外false
	bool ret = (hp <= 0);
	return ret;
}

int Enemy::GetPoint()//
{
	return point;
}
