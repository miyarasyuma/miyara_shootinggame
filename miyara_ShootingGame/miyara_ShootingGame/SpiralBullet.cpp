#include "SpiralBullet.h"
#include"DxLib.h"
#include<math.h>
#define PI 3.14159

SpiralBullet::SpiralBullet(T_Location location, T_Location speed):BulletsBase(location, 5.f, 1, speed)
{

}

void SpiralBullet::Update()
{
	T_Location newLocation = GetLocation();
	newLocation.y -= (speed.y * cos(30 * PI));
}

void SpiralBullet::Draw()
{
	DrawCircle(GetLocation().x, GetLocation().y, GetRadius(), GetColor(255, 255, 255));
}

bool SpiralBullet::isScreenOut()
{
	//íeÇ™äÆëSÇ…âÊñ äOÇ…çsÇ≠Ç∆è¡Ç¶ÇÈ
	bool ret = (GetLocation().y + GetRadius() <= 0 || GetLocation().y + GetRadius() >= 720);
	     ret= (GetLocation().x + GetRadius() <= 0 || GetLocation().x + GetRadius() >= 1280);

	return ret;
}