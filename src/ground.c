#include "ground.h"
#include "simple_logger.h"

void ground_update(Entity* self);

Entity* Ground_New(Vector3D pos, float scale, char* name) {
	Entity* ground = NULL;
	ground = gf3d_entity_new();
	if (!ground) {
		slog("failed to create ground");
		return;
	}
	ground->tag = "ground";
	ground->name = name;
	ground->position = pos;
	gfc_matrix_identity(ground->modelMat);
	ground->model = gf3d_model_load_animated("sphere_anim", "white", 1, 3);
	ground->shape = gf3d_shape_sphere(scale, pos);
	gfc_matrix_translate(ground->modelMat, pos);
	gfc_matrix_scale(ground->modelMat, scale);
	ground->frame = 1;
	gf3d_body_set(
		&ground->body,
		0,
		0,
		0,
		0,
		ground->position,
		vector3d(0, 0, 0),
		1,
		0,
		0,
		&ground->shape,
		NULL,
		NULL);
	ground->update = ground_update;
	ground->shape.data = ground;
	return ground;
}

Entity* ground_spawn(Vector3D position, SJson* args) {

	
	return Ground_New(position, 5, "ground");

}

void ground_update(Entity* self) {
	//slog("%s", self->name);
	if (strcmp(self->name, "ground2") == 0) {
		//self->velocity.z -= 0.001;
		//gf3d_entity_move(self, self->velocity);
	}
}