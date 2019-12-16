#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "entity.h"
#include "simple_json.h"

Entity* Player_New(Vector3D position);

void Player_Free();

Entity* player_spawn(Vector3D position, SJson* args);

Entity* player_get();

int player_lives_get();

#endif // !__PLAYER_H__
