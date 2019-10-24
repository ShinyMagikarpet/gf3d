#include "ground.h"

Entity* Ground_New(Vector3D pos, float scale) {
	Entity* ground = gf3d_entity_new();
	ground->position = pos;
	gfc_matrix_identity(ground->modelMat);
	ground->model = gf3d_model_load_animated("sphere_anim", 1, 3);
	ground->shape = gf3d_shape_sphere(scale, pos);
	gfc_matrix_translate(ground->modelMat, pos);
	ground->modelMat[3][3] -= scale;
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
}