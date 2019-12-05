#include "collectable.h"
#include "simple_logger.h"

typedef struct {
	Collectable* collectable_list;
	Uint32 collectable_size;
	Uint32 spawnCount;
}CollectableManager;

static CollectableManager collectable_manager = { 0 };

void collectable_update(Entity* self);

void collectable_manager_close() {

	if (collectable_manager.collectable_list != NULL)
	{
		free(collectable_manager.collectable_list);
	}
	memset(&collectable_manager, 0, sizeof(CollectableManager));
}

void collectable_manager_init(Uint32 collectable_max) {

	collectable_manager.collectable_list = (Collectable*)gfc_allocate_array(sizeof(Collectable), collectable_max);
	if (!collectable_manager.collectable_list)
	{
		slog("failed to allocate collectable list");
		return;
	}
	collectable_manager.collectable_size = collectable_max;
	slog("collectable system initialized with size of %i", collectable_manager.collectable_size);
	atexit(collectable_manager_close);
}

Collectable* collectable_new_object()
{
	Collectable* col = NULL;
	int i;
	for (i = 0; i < collectable_manager.collectable_size; i++)
	{
		if (collectable_manager.collectable_list[i]._inuse)continue;
		memset(&collectable_manager.collectable_list[i], 0, sizeof(Entity));
		collectable_manager.collectable_list[i]._inuse = 1;
		collectable_manager.collectable_list[i].collected = 0;
		collectable_manager.spawnCount++;
		return &collectable_manager.collectable_list[i];
	}
	slog("request for entity failed: all full up");
	return NULL;
}

Collectable* Collectable_New(Vector3D position, CollectableColor color) {

	if (collectable_manager.collectable_size == 0) {
		collectable_manager_init(8);
	}

	Collectable* collectable = collectable_new_object();
	if (!collectable) {
		return NULL;
	}
	collectable->ent = gf3d_entity_new();
	if (!collectable->ent) {
		slog("Couldn't make entity");
		return collectable;
	}

	collectable->ent->tag = "collectable";
	collectable->ent->name = "coin";
	collectable->ent->position = position;
	gfc_matrix_identity(collectable->ent->modelMat);
	switch (color) {
	case Collectable_Red:
		collectable->ent->model = gf3d_model_load_animated("Coin", "red", 1, 13);
		collectable->sprite = gf3d_sprite_load("images/red.png", 64, 64, 1);
		vector2d_copy(collectable->sprite->position, vector2d(1000, 10));
		break;
	case Collectable_Blue:
		collectable->ent->model = gf3d_model_load_animated("Coin", "blue", 1, 13);
		collectable->sprite = gf3d_sprite_load("images/blue.png", 64, 64, 1);
		vector2d_copy(collectable->sprite->position, vector2d(1040, 10));
		break;
	case Collectable_Yellow:
		collectable->ent->model = gf3d_model_load_animated("Coin", "yellow", 1, 13);
		collectable->sprite = gf3d_sprite_load("images/yellow.png", 64, 64, 1);
		vector2d_copy(collectable->sprite->position, vector2d(1080, 10));
		break;
	default:
		collectable->ent->model = gf3d_model_load_animated("Coin", "white", 1, 13);
	}
	collectable->ent->shape = gf3d_shape_sphere(1, position);
	gfc_matrix_translate(collectable->ent->modelMat, position);
	collectable->ent->frame = 1;
	gf3d_body_set(
		&collectable->ent->body,
		0,
		0,
		0,
		0,
		collectable->ent->position,
		vector3d(0, 0, 0),
		1,
		0,
		0,
		&collectable->ent->shape,
		collectable->ent,
		NULL);

	collectable->ent->shape.data = collectable->ent;
	collectable->color = color;
	collectable->ent->update = collectable_update;
	collectable->ent->data = collectable;
	return collectable;
}

Entity* collectable_spawn(Vector3D position, cJSON* args) {

	//return NULL;
	CollectableColor color = -1;
	if (args) {
		if (strcmp(args->valuestring, "yellow") == 0) {
			color = Collectable_Yellow;
		}
		else if (strcmp(args->valuestring, "red") == 0) {
			color = Collectable_Red;
		}
		else if (strcmp(args->valuestring, "blue") == 0) {
			color = Collectable_Blue;
		}
		else {
			slog("Json could not parse color for collectable");
			return NULL;
		}
	}

	Collectable* collectable = Collectable_New(position, color);
	if (!collectable->ent) {
		slog("No ent for collectable");
		return NULL;
	}
	return collectable->ent;

}

void free_collectable(Collectable* collectable) {
	if (!collectable) {
		return;
	}
	free(collectable);
}

int check_win_condition() {

	int win = 0;

	for (int i = 0; i < collectable_manager.spawnCount; i++) {

		if (collectable_manager.collectable_list[i]._inuse) {
			if (collectable_manager.collectable_list[i].collected == 0) {
				break;
			}
			win++;
		}
	}

	if (win == collectable_manager.spawnCount) {
		slog("Win condition met");
		return 1;
	}
	slog("Didn't meet win condition yet");
	return 0;
}

void collectable_update(Entity* self) {

	if (self->_inuse == 0) {
		return;
	}

	self->frame += 1;
	if (self->frame > self->model->frameCount-1) {
		self->frame = 0;
	}
}