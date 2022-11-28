#pragma once
#include "BulletsBase.h"
class SpiralBullet : public BulletsBase
{
public:
	SpiralBullet(T_Location location, T_Location speed);

public:
	virtual void Update() override;
	virtual void Draw() override;
	virtual bool isScreenOut() override;
};

