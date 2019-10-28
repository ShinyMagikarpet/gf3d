#include "collectable.h"
#include "simple_logger.h"

void collectable_update(Entity* self);

Collectable Collectable_New(Vector3D position, CollectableColor color) {
	
	Collectable collectable = { 0 };
	collectable.ent = gf3d_entity_new();
	if (!collectable.ent) {
		slog("Couldn't make entity");
		return collectable;
	}

	collectable.ent->tag = "collectable";
	collectable.ent->name = "coin";
	collectable.ent->position = position;
	gfc_matrix_identity(collectable.ent->modelMat);
	switch (color) {
	case Collectable_Red:
		collectable.ent->model = gf3d_model_load_animated("Coin", "red", 1, 13);
		break;
	case Collectable_Blue:
		collectable.ent->model = gf3d_model_load_animated("Coin", "blue", 1, 13);
		break;
	case Collectable_Yellow:
		collectable.ent->model = gf3d_model_load_animated("Coin", "yellow", 1, 13);
		break;
	default:
		collectable.ent->model = gf3d_model_load_animated("Coin", "white", 1, 13);
	}
	collectable.ent->shape = gf3d_shape_sphere(1, position);
	gfc_matrix_translate(collectable.ent->modelMat, position);
	collectable.ent->frame = 1;
	gf3d_body_set(
		&collectable.ent->body,
		0,
		0,
		0,
		0,
		collectable.ent->position,
		vector3d(0, 0, 0),
		1,
		0,
		0,
		&collectable.ent->shape,
		collectable.ent,
		NULL);

	collectable.ent->shape.data = collectable.ent;
	collectable.color = color;
	collectable.ent->update = collectable_update;
	collectable.ent->data = &collectable;
	return collectable;
}

void collectable_update(Entity* self) {
	self->frame += 1;
	if (self->frame > self->model->frameCount-1) {
		self->frame = 0;
	}
}