#include"DxLib.h"
#include"StraightBullets.h"
#include "SpiralBullet.h"
#include "Enemy.h"

#define _ENEMY_BULLET_ALL_ 100

T_Location locations[3] = {
    { 640 ,200 },
    { 1200,200 },
    { 200 ,200 }
};

int next[3] = {
	1,
	2,
	1
};

int current = 0;

Enemy::Enemy(T_Location location) :CharaBase(location, 20.f, T_Location{1.4,1})
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
	  Move();


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

void Enemy::Move()
{
	T_Location nextLocation = GetLocation();//��������W�������Ă���

	if ((nextLocation.y == locations[current].y) &&  //�������W�ɂ����玟�̍��W�Ɉړ�����
		(nextLocation.x == locations[current].x))
	{
		current = next[current];
	}
	else
	{//�ړI�n�ɂ��Ȃ�������
		if (nextLocation.y != locations[current].y)
		{
			if (nextLocation.y < locations[current].y)//��������W���傫����������Z���čs��
			{
				nextLocation.y += speed.y;
				if ((GetLocation().y <= locations[current].y) && (locations[current].y <= nextLocation.y))//���̍��W���ړI�n���ł����Ƃ�
				{
					nextLocation.y = locations[current].y;//�ړI�n���щz�����Ƃ��ɑ�����ē������W�ɂ���
				}
			}
			else
			{
				nextLocation.y -= speed.y;
				if ((nextLocation.y <= locations[current].y) && (locations[current].y <= GetLocation().y))//���̍��W���ړI�n���ł����Ƃ�
				{
					nextLocation.y=locations[current].y;//�ړI�n���щz�����Ƃ��ɑ�����ē������W�ɂ���
				}
			}
		}
		if (nextLocation.x != locations[current].x)
		{
			if (nextLocation.x < locations[current].x)
			{
				nextLocation.x += speed.x;
				if ((GetLocation().x <= locations[current].x) && (locations[current].x <= nextLocation.x))
				{
					nextLocation.x = locations[current].x;
				}
			}
			else
			{
				nextLocation.x -= speed.x;
				if((nextLocation.x<= locations[current].x)&&(locations[current].x <= GetLocation().x))
					{
					nextLocation.x = locations[current].x;
                    }
			}
		}
	}

	SetLocation(nextLocation);
}