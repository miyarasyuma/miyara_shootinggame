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

		//画面外に行ったら弾を消す
		if (bullets[bulletCount]->isScreenOut())//画面外で消えたか確かめる
		{
			DeleteBullet(bulletCount);
			bulletCount--;
		}
	}
	if (bulletCount < 30 && bullets[bulletCount] == nullptr)
	{
		//enemyの弾幕を生成
		bullets[bulletCount] = new SpiralBullet(GetLocation(),2.f,(10*shotNum));
		shotNum++;
		//bullets[bulletCount]=new StraightBullets(GetLocation(),T_Location)
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

void Enemy::Move()
{
	T_Location nextLocation = GetLocation();//今いる座標から取ってくる

	if ((nextLocation.y == locations[current].y) &&  //同じ座標にいたら次の座標に移動する
		(nextLocation.x == locations[current].x))
	{
		current = next[current];
	}
	else
	{//目的地にいなかったら
		if (nextLocation.y != locations[current].y)
		{
			if (nextLocation.y < locations[current].y)//今いる座標より大きかったら加算して行く
			{
				nextLocation.y += speed.y;
				if ((GetLocation().y <= locations[current].y) && (locations[current].y <= nextLocation.y))//今の座標より目的地がでかいとき
				{
					nextLocation.y = locations[current].y;//目的地を飛び越えたときに代入して同じ座標にする
				}
			}
			else
			{
				nextLocation.y -= speed.y;
				if ((nextLocation.y <= locations[current].y) && (locations[current].y <= GetLocation().y))//今の座標より目的地がでかいとき
				{
					nextLocation.y=locations[current].y;//目的地を飛び越えたときに代入して同じ座標にする
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