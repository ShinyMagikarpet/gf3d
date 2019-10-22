#include "gf3d_space.h"
#include "simple_logger.h"
#include "gf3d_dynamic_body.h"

Space* gf2d_space_new_full(
	int         precision,
	float       timeStep,
	Vector3D    gravity,
	float       dampening,
	float       slop)
{
	Space* space;
	space = gf2d_space_new();
	if (!space)return NULL;
	vector3d_copy(space->gravity, gravity);
	space->timeStep = timeStep;
	space->precision = precision;
	space->dampening = dampening;
	space->slop = slop;
	return space;
}

Space* gf2d_space_new()
{
	Space* space;
	space = (Space*)malloc(sizeof(Space));
	if (!space)
	{
		slog("failed to allocate space for Space");
		return NULL;
	}
	memset(space, 0, sizeof(Space));
	space->dynamicBodyList = gfc_list_new();
	space->staticShapes = gfc_list_new();
	return space;
}

void gf3d_space_free(Space* space)
{
	if (!space)return;

	//static shapes ARE owned by the space, so are deleted when the space goes away
	//gf2d_list_foreach(space->staticShapes, gf2d_free_shapes, NULL);
	//gf2d_list_foreach(space->dynamicBodyList, gf2d_free_dynamic_bodies, NULL);
	gfc_list_delete(space->dynamicBodyList);
	gfc_list_delete(space->staticShapes);
	free(space);
	slog("Successfully deleted space");
}

void gf3d_space_step(Space* space, float t)
{
	//DynamicBody* db = NULL;
	int i, count;
	if (!space)return;
	count = gfc_list_get_count(space->dynamicBodyList);
	for (i = 0; i < count;i++)
	{
		//db = (DynamicBody*)gf2d_list_get_nth(space->dynamicBodyList, i);
		//if (!db)continue;
		//if (db->blocked)
		//{
		//	continue;// no need to move something that has already collided
		//}
		//gf2d_space_dynamic_bodies_step(space, db, t);
	}
}

void gf3d_space_update(Space* space)
{
	float s;
	float loops = 0;
	if (!space)return;
	//gf2d_space_fix_overlaps(space, 8);
	//gf2d_space_reset_bodies(space);
	// reset all body tracking
	for (s = 0; s <= 1; s += space->timeStep)
	{
		gf3d_space_step(space, s);
		loops = loops + 1;
	}
	//gf2d_space_update_bodies(space, loops);
}

void gf3d_space_add_static_shape(Space* space, Shape shape)
{
	Shape* newShape;
	if (!space)
	{
		slog("no space provided");
		return;
	}
	newShape = (Shape*)malloc(sizeof(shape));
	if (!newShape)
	{
		slog("failed to allocate new space for the shape");
		return;
	}
	memcpy(newShape, &shape, sizeof(Shape));
	space->staticShapes = gfc_list_append(space->staticShapes, (void*)newShape);
}

//void gf2d_space_add_body(Space* space, Body* body)
//{
//	DynamicBody* db = NULL;
//	if (!space)
//	{
//		slog("no space provided");
//		return;
//	}
//	if (!body)
//	{
//		slog("no body provided");
//		return;
//	}
//	db = gf3d_dynamic_body_new();
//	if (!db)return;
//	db->body = body;
//	db->id = space->idpool++;
//	space->dynamicBodyList = gf2d_list_append(space->dynamicBodyList, (void*)db);
//}


