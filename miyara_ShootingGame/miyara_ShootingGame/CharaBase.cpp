#include "CharaBase.h"

CharaBase::CharaBase(T_Location locatiom, float radius, T_Location speed) : SphereCollider(locatiom,radius),speed(speed),image(nullptr)
{

}