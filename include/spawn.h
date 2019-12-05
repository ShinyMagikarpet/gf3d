#ifndef __SPAWN_H__
#define __SPAWN_H__

#include "simple_json.h"
#include "entity.h"
#include "cJSON.h"

typedef struct
{
	const char* name;
	Entity* (*spawn)(Vector3D, SJson* args);
}Spawn;

void spawn_entity(const char* name, Vector3D position, Uint32 id, cJSON* args);

#endif // !__SPAWN_H__

