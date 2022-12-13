#include"DxLib.h"
#include"StraightBullets.h"
#include "SpiralBullet.h"
#include "Enemy.h"

#define _ENEMY_BULLET_ALL_ 100

T_Location locations[4] = {
	{ 640. -10 },
    { 640.200 },
    { 1200.500 },
    { 200.400 }
};

Enemy::Enemy(T_Location location) :CharaBase(location, 20.f, T_Location{0,1})
,hp(10),point(100),shotNum(0)
{
	bullets = new BulletsBase * [30];
	for (int i = 0; i < 30; i++)
	{
		bullets[i] = nullptr;
	}


}

void Enemy::Update()
{
		//T_Location newLocation = GetLocation();
		//newLocation.y += speed.y;
		//SetLocation(newLocation);
	T_Location newLocation = GetLocation();
		if (GetLocation().y <= locations[1].y)
		{
			newLocation.y += speed.y;
			SetLocation(newLocation);
		}


	int bulletCount;
	for (bulletCount = 0; bulletCount < 30; bulletCount++)
	{
		if (bullets[bulletCount] == nullptr)
		{
			break;
		}
		bullets[bulletCount]->Update();

		//��ʊO�ɍs������e������
		if (bullets[bulletCount]->isScreenOut())//��ʊO�ŏ��������m���߂�
		{
			DeleteBullet(bulletCount);
			bulletCount--;
		}
	}
	if (bulletCount < 30 && bullets[bulletCount] == nullptr)
	{
		//enemy�̒e���𐶐�
		bullets[bulletCount] = new SpiralBullet(GetLocation(),2.f,(10*shotNum));
		shotNum++;
		//bullets[bulletCount]=new StraightBullets(GetLocation(),T_Location)
	}
}

void Enemy::Draw()
{
	DrawCircle(GetLocation().x, GetLocation().y, GetRadius(), GetColor(0, 0, 255));//�G�̖{��

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

bool Enemy::HpCheck()//Enemy�̗̑�	
{
	//�O�ɂȂ�����true,0�ȊOfalse
	bool ret = (hp <= 0);
	return ret;
}

int Enemy::GetPoint()//
{
	return point;
}
