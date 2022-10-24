#pragma once
#include "CharaBase.h"
class Enemy : public CharaBase
{
private:
	int hp;
	int point;

public:
	void Update() override;
	void Draw() override;
	void Hit() override;
	bool HpCheck();
	int GetPoint();

};

