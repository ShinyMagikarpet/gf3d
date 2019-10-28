#include "simple_logger.h"
#include "entity.h"

typedef struct
{
	Entity* entity_list;
	Uint32  entity_max;
}EntityManager;

static EntityManager gf3d_entity_manager = { 0 };

void gf3d_entity_manager_close()
{
	if (gf3d_entity_manager.entity_list != NULL)
	{
		free(gf3d_entity_manager.entity_list);
	}
	memset(&gf3d_entity_manager, 0, sizeof(EntityManager));
}

void gf3d_entity_manager_init(Uint32 entity_max)
{
	gf3d_entity_manager.entity_list = (Entity*)gfc_allocate_array(sizeof(Entity), entity_max);
	if (!gf3d_entity_manager.entity_list)
	{
		slog("failed to allocate entity list");
		return;
	}
	gf3d_entity_manager.entity_max = entity_max;
	slog("Entity system initialized with size of %i", gf3d_entity_manager.entity_max);
	atexit(gf3d_entity_manager_close);
}

Entity* gf3d_entity_new()
{
	Entity* ent = NULL;
	int i;
	for (i = 0; i < gf3d_entity_manager.entity_max; i++)
	{
		if (gf3d_entity_manager.entity_list[i]._inuse)continue;
		//. found a free entity
		memset(&gf3d_entity_manager.entity_list[i], 0, sizeof(Entity));
		gf3d_entity_manager.entity_list[i]._inuse = 1;
		gf3d_entity_manager.entity_list[i]._ID = i;
		slog("Generated new entity");
		return &gf3d_entity_manager.entity_list[i];
	}
	slog("request for entity failed: all full up");
	return NULL;
}

void gf3d_entity_free(Entity* self)
{
	if (!self)
	{
		slog("self pointer is not valid");
		return;
	}
	self->_inuse = 0;
	gf3d_model_free(self->model);
	if (self->data != NULL)
	{
		slog("warning: data not freed at entity free!");
	}
}

void gf3d_entity_draw(Entity* self, Uint32 bufferFrame, VkCommandBuffer commandBuffer)
{

	if (!self)return;
	
	gf3d_model_draw(self->model, bufferFrame, commandBuffer, self->modelMat, self->frame);

}

void gf3d_entity_draw_all(Uint32 bufferFrame, VkCommandBuffer commandBuffer) {

	int i;
	for (i = 0; i < gf3d_entity_manager.entity_max; i++) {
		if (gf3d_entity_manager.entity_list[i]._inuse == 0) {
			continue;
		}
		gf3d_entity_draw(&gf3d_entity_manager.entity_list[i], bufferFrame, commandBuffer);
	}
}

void gf3d_entity_think(Entity* self) {

	if (!self)return;
	if (!self->_inuse)return;

	if (self->think != NULL) {
		self->think(self);
	}
}

void gf3d_entity_think_all() {

	int i;
	for (i = 0; i < gf3d_entity_manager.entity_max; i++) {
		if (gf3d_entity_manager.entity_list[i]._inuse == 0) {
			continue;
		}
		gf3d_entity_think(&gf3d_entity_manager.entity_list[i]);
	}
}

void gf3d_entity_update(Entity* self) {

	if (!self)return;
	if (!self->_inuse)return;

	if (self->update != NULL) {
		self->update(self);
	}
}

void gf3d_entity_update_all() {

	int i;
	for (i = 0; i < gf3d_entity_manager.entity_max; i++) {
		if (gf3d_entity_manager.entity_list[i]._inuse == 0) {
			continue;
		}
		gf3d_entity_update(&gf3d_entity_manager.entity_list[i]);
	}
}

void gf3d_entity_move(Entity* ent, Vector3D dir) {

	vector3d_add(ent->position, ent->position, dir);
	gfc_matrix_make_translation(ent->modelMat, ent->position);
}

Body* get_entity_bodies(int i) {
	return &gf3d_entity_manager.entity_list[i].body;
}

Uint32 get_entity_size() {
	int size = 0;
	for (int i = 0; i < gf3d_entity_manager.entity_max; i++) {
		//slog("entity usage = %i", gf3d_entity_manager.entity_list[i]._inuse);
		if (gf3d_entity_manager.entity_list[i]._ID == i) {
			size++;
			continue;
		}
	}

	return size;
}

void slog_entity_positions() {

	Entity* ent;
	for (int i = 0; i < get_entity_size(); i++) {
		ent = &gf3d_entity_manager.entity_list[i];
		slog("Position: %f, %f, %f", ent->position.x, ent->position.y, ent->position.z);
	}
}

void slog_entity_names() {

	Entity* ent;
	for (int i = 0; i < get_entity_size(); i++) {
		ent = &gf3d_entity_manager.entity_list[i];
		slog("Entity name: %s", ent->name);
	}
}
