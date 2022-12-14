#include "StraightBullets.h"
#include"DxLib.h"
StraightBullets::StraightBullets(T_Location location, T_Location speed) :BulletsBase(location, 5.f, 1, speed)
{

}

void  StraightBullets::Update()
{
	T_Location newLocation = GetLocation();
	newLocation.y -= speed.y;
	//newLocation.y += speed.y;
	SetLocation(newLocation);
}

void  StraightBullets::Draw()
{
	DrawCircle(GetLocation().x, GetLocation().y, GetRadius(), GetColor(255, 255, 255));
}

bool StraightBullets::isScreenOut()
{
	//弾が完全に画面外に行くと消える
	bool ret = (GetLocation().y + GetRadius() <= 0 || GetLocation().y + GetRadius() >= 720);

	return ret;

}