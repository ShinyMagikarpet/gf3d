#include "Player.h"
#include "gfc_input.h"
#include "gf3d_camera.h"
#include "gf3d_space.h"
#define MOVE_SPEED 1
static Entity* player = NULL;

void player_think(Entity* self);
void player_update(Entity* self);


Entity* Player_New() {

	player = gf3d_entity_new();
	player->model = gf3d_model_load("sphere");
	gfc_matrix_identity(player->modelMat);

	player->position = vector3d(0, 0, 0);
	player->shape = gf3d_shape_sphere(1, player->position);
	player->think = player_think;

	return player;
}

void player_think(Entity* self) {

	if (gfc_input_key_down("a")) {

		/*gfc_matrix_rotate(
			player->modelMat,
			player->modelMat,
			0.002,
			vector3d(0, 0, -1)
		);*/

		gf3d_entity_move(self, vector3d(MOVE_SPEED, 0, 0));

	}

	if (gfc_input_key_down("d")) {

		/*gfc_matrix_rotate(
			player->modelMat,
			player->modelMat,
			0.002,
			vector3d(0, 0, -1)
		);*/

		gf3d_entity_move(self, vector3d(-MOVE_SPEED, 0, 0));

	}

	if (gfc_input_key_down("w")) {

		gf3d_entity_move(self, vector3d(0, -MOVE_SPEED, 0));

	}

	if (gfc_input_key_down("s")) {

		/*gfc_matrix_rotate(
			player->modelMat,
			player->modelMat,
			0.002,
			vector3d(0, 0, -1)
		);*/

		gf3d_entity_move(self, vector3d(0, MOVE_SPEED, 0));

	}



	if (gfc_input_key_down("q")) {

		gfc_matrix_rotate(
			self->modelMat,
			self->modelMat,
			0.002,
			vector3d(0, 0, 1)
		);

		//gfc_matrix_translate(player->modelMat, vector3d(0, 0.01, 0));


	}

	if (gfc_input_key_down("e")) {

		gfc_matrix_rotate(
			self->modelMat,
			self->modelMat,
			0.002,
			vector3d(0, 0, -1)
		);

		//gfc_matrix_translate(player->modelMat, vector3d(0, 0.01, 0));

		
	}

	//gf3d_entity_move(self, vector3d(0, 0, -9));
	player->shape.s.s.point.pos = player->position;

}

void player_update(Entity* self) {

	//gf3d_entity_move(self, vector3d(0, 0, 1));
}