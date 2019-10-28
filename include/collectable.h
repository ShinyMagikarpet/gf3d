#ifndef __COLLECTABLE_H__
#define __COLLECTABLE_H__

#include "entity.h"

typedef enum
{
	Collectable_Red,
	Collectable_Yellow,
	Collectable_Blue
}CollectableColor;

typedef struct Collectable_S {

	Entity* ent;
	CollectableColor color;

}Collectable;

Collectable Collectable_New(Vector3D position, CollectableColor color);
#endif // !__COLLECTABLE_H__
