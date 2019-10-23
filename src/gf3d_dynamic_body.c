#include "gf3d_dynamic_body.h"
#include "simple_logger.h"

Shape gf3d_dynamic_body_to_shape(DynamicBody* a)
{
	Shape aS = { 0 };
	if (!a)return aS;
	gf3d_shape_copy(&aS, *a->body->shape);
	gf3d_shape_move(&aS, a->position);
	return aS;
}

DynamicBody* gf3d_dynamic_body_new() {

	DynamicBody* db;
	db = (DynamicBody*)malloc(sizeof(DynamicBody));
	if (!db)
	{
		slog("failed to allocation data for a new dynamic body");
		return NULL;
	}
	memset(db, 0, sizeof(DynamicBody));
	db->collisionList = gfc_list_new();
	return db;
}

void gf3d_dynamic_body_free(DynamicBody* db)
{
	if (!db)return;
	//cleanup collionList
	gf3d_dynamic_body_clear_collisions(db);
	free(db);
}

void gf3d_dynamic_body_reset(DynamicBody* db, float factor) {

	if (!db)return;
	db->blocked = 0;
	gf3d_dynamic_body_clear_collisions(db);
	vector3d_copy(db->position, db->body->position);
	vector3d_scale(db->velocity, db->body->velocity, factor);
	db->speed = vector3d_magnitude(db->velocity);
}

void gf3d_dynamic_body_update(DynamicBody* db, float factor) {

	if (!db)return;
	if (!db->body)return;
	vector3d_copy(db->body->position, db->position);
	vector3d_scale(db->body->velocity, db->velocity, factor);
}

Collision* gf3d_dynamic_body_collision_check(DynamicBody* dba, DynamicBody* dbb, float timeStep) {

	Collision* collision = NULL;
	if ((!dba) || (!dbb))return NULL;
	if ((!dba->body) || (!dbb->body))
	{
		slog("cannot do collision check, body missing from one or more DynamicBody");
		return NULL;
	}
	if ((dba->body->team) && (dbb->body->team) && (dba->body->team != dbb->body->team))
	{
		return NULL;
	}
	if (!dba->body->cliplayer)
	{
		return NULL;
	}
	if (!gf3d_shape_overlap(gf3d_dynamic_body_to_shape(dba), gf3d_dynamic_body_to_shape(dbb)))
	{
		return NULL;
	}
	collision = gf3d_collision_new();
	if (!collision)return NULL;
	collision->body = dbb->body;
	collision->timeStep = timeStep;
	//TODO: collision->pointOfContact;
	//collision->normal = gf3d_shape_get_normal_for_shape(gf3d_dynamic_body_to_shape(dbb), gf3d_dynamic_body_to_shape(dba));
	collision->shape = dbb->body->shape;
	if (dba->body->cliplayer & dbb->body->cliplayer)
	{
		dba->blocked = 1;
	}
	return collision;
}

void gf3d_dynamic_body_clear_collisions(DynamicBody* db)
{
	if (!db)return;
	gf3d_collision_list_free(db->collisionList);
	db->collisionList = gfc_list_new();
}