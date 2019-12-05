#ifndef __COLLECTABLE_H__
#define __COLLECTABLE_H__

#include "entity.h"
#include "gf3d_sprite.h"
#include "cjson.h"

typedef enum
{
	Collectable_Red,
	Collectable_Yellow,
	Collectable_Blue
}CollectableColor;

typedef struct Collectable_S {

	Entity* ent;
	CollectableColor color;
	Sprite* sprite;

}Collectable;

Collectable* Collectable_New(Vector3D position, CollectableColor color);

Entity* collectable_spawn(Vector3D position, cJSON* args);

void free_collectable(Collectable* collectable);

int check_win_condition();

#endif // !__COLLECTABLE_H__
