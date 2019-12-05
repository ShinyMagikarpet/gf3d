#include "level.h"
#include "Player.h"
#include "simple_logger.h"
#include "gfc_text.h"
#include "gf3d_config.h"
#include "cJSON.h"
#include "spawn.h"



void level_info_free(LevelInfo* linfo){

	if (!linfo)return;
	//sj_free(linfo->spawnList);
	cJSON_free(linfo->spawnList);
	free(linfo);
}

LevelInfo* level_info_new(){

	LevelInfo* linfo = NULL;
	linfo = (LevelInfo*)malloc(sizeof(LevelInfo));
	if (!linfo)
	{
		slog("failed to allocate level info");
		return NULL;
	}
	memset(linfo, 0, sizeof(LevelInfo));
	return linfo;

}

LevelInfo* level_info_create(const char* backgroundImage, const char* backgroundMusic){

	LevelInfo* linfo = NULL;
	linfo = level_info_new();
	if (!linfo)return NULL;
	gfc_line_cpy(linfo->backgroundImage, backgroundImage);
	gfc_line_cpy(linfo->backgroundMusic, backgroundMusic);
	return linfo;

}

typedef struct
{
	SJString* key;  /**<the identifying key*/
	SJson* value;   /**<the value the key references*/
}SJPair;

LevelInfo* level_info_load(char* filename){

	LevelInfo* linfo = NULL;
	SJson* json, * world;
	if (!filename)return NULL;
	json = sj_load(filename);
	if (!json)
	{
		slog("failed to load level file %s", filename);
		return NULL;
	}

	linfo = level_info_new();

	if (!linfo){
		return NULL;
	}

	world = sj_object_get_value(json, "world");

	if (!world){
		slog("missing world object in level file %s", filename);
		sj_free(json);
		level_info_free(linfo);
		return NULL;
	}

	/*int value = 0;
	sj_get_integer_value(sj_object_get_value(world, "myVal"),&value);
	slog("Value is %i", value);*/
	//gfc_line_cpy(linfo->backgroundMusic, sj_get_string_value(sj_object_get_value(world, "backgroundMusic")));
	//SJson* mySon = NULL;
	//mySon = sj_copy(sj_object_get_value(world, "spawnList"));

	//linfo->spawnList = sj_copy(sj_object_get_value(world, "spawnList"));
	//int count = sj_array_get_count(linfo->spawnList);
	//slog("Spawn list count = %i", count);

	//TODO stuff here
	//linfo->transitionList = sj_copy(sj_object_get_value(world, "transitionList"));
	//count = sj_array_get_count(linfo->transitionList);
	//slog("Transition list count = %i", count);

	char* string = read_file_for_cjson(filename);

	cJSON* example = cJSON_Parse(string);
	if (example == NULL) {
		slog("This is null");
	}
	else {
		slog("it's aight");
	}

	cJSON* world2 = cJSON_GetObjectItemCaseSensitive(example, "world");
	cJSON* spawnList = cJSON_GetObjectItemCaseSensitive(world2, "spawnList");
	linfo->spawnList = spawnList;
	/*if (spawnList) {
		cJSON* spawn = NULL;
		cJSON_ArrayForEach(spawn, spawnList) {
			cJSON* position = cJSON_GetObjectItemCaseSensitive(spawn, "position");
			Vector3D vec3 = cjson_value_as_vector3d(position);
			slog("Position: %f %f %f", vec3.x, vec3.y, vec3.z);
		}

	}*/
	//cJSON* grape = cJSON_GetObjectItemCaseSensitive(example, "test");
	//slog(grape->valuestring);
	cJSON_free(example);
	cJSON_free(world2);
	free(string);
	sj_free(json);
	//slog("loaded level info for %s", filename);
	return linfo;
}

void level_spawn_entities(cJSON* spawnList){
	int i = 0, count = 0;
	Vector3D position;
	int id = 0;
	cJSON* item = NULL;

	cJSON_ArrayForEach(item, spawnList) {
		slog(item->child->valuestring);
		position = cjson_value_as_vector3d(item->child->next);
		spawn_entity(item->child->valuestring, position, 0, item->child->next->next);
	}

	cJSON_free(item);
	/*for (i = 0; i < count; i++)
	{
		item = sj_array_get_nth(spawnList, i);
		if (!item)continue;
		sj_value_as_vector3d(sj_object_get_value(item,"position"), &position);
		if (!sj_get_integer_value(sj_object_get_value(item, "name"), &id))
		{
			id = 0;
		}
		spawn_entity(sj_get_string_value(sj_object_get_value(item, "name")), position, id, sj_object_get_value(item, "args"));
	}*/
}
