#ifndef __GROUND_H__
#define __GROUND_H__

#include "entity.h"
#include "simple_json.h"

Entity* Ground_New(Vector3D pos, float scale, char* name);

Entity* ground_spawn(Vector3D position, SJson* args);

#endif // !__GROUND_H__

