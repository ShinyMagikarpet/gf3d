#include <stdlib.h>
#include <string.h>

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
	
	gf3d_model_draw(self->model, bufferFrame, commandBuffer, self->modelMat);

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

//void gf2d_entity_draw_all() {
//	int i;
//	for (i = 0; i < entityManager.maxEntities; i++) {
//		if (entityManager.entityList[i].inuse == 0)continue;
//		gf2d_entity_draw(&entityManager.entityList[i]);
//	}
//}

