#include"DxLib.h"
#include"StraightBullets.h"
#include "SpiralBullet.h"
#include "Enemy.h"

Enemy::Enemy(T_Location location) :CharaBase(location, 20.f, T_Location{0,1})
,hp(10),point(100),shotNum(0)
{
	bullets = new BulletsBase * [_ENEMY_BULLET_ALL_];
	for (int i = 0; i < _ENEMY_BULLET_ALL_; i++)
	{
		bullets[i] = nullptr;
	}
}

void Enemy::Update()
{
	/*T_Location newLocation = GetLocation();
	newLocation.y += speed.y;
	SetLocation(newLocation);*/



	int bulletCount;
	for (bulletCount = 0; bulletCount < _ENEMY_BULLET_ALL_; bulletCount++)
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
	if (bulletCount < _ENEMY_BULLET_ALL_ && bullets[bulletCount] == nullptr)
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

	for (int bulletCount = 0; bulletCount < _ENEMY_BULLET_ALL_; bulletCount++)
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
