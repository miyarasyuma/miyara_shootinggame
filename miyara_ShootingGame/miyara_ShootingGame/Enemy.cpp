#include"DxLib.h"
#include "Enemy.h"

Enemy::Enemy(T_Location location) :CharaBase(location, 20.f, T_Location{0,0.5}),hp(10),point(10)
{

}

void Enemy::Update()
{
	T_Location newLocation = GetLocation();
	newLocation.y += 0.5; 
	SetLocation(newLocation);
}

void Enemy::Draw()
{
	DrawCircle(GetLocation().x, GetLocation().y, GetRadius(), GetColor(0, 0, 255));
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

bool Enemy::HpCheck()//Enemy‚Ì‘Ì—Í	
{
	//‚O‚É‚È‚Á‚½‚çtrue,0ˆÈŠOfalse
	bool ret = (hp <= 0);
	return ret;
}

int Enemy::GetPoint()//
{
	return point;
}
