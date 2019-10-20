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
	player->model = gf3d_model_load("dino");
	gfc_matrix_identity(player->modelMat);

	player->position = vector3d(0, 0, 0);
	
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
		player->position.x += MOVE_SPEED;
		gfc_matrix_make_translation(self->modelMat, player->position);
		//gf3d_camera_move(vector3d(1, 0, 0));
		


	}

	if (gfc_input_key_down("d")) {

		/*gfc_matrix_rotate(
			player->modelMat,
			player->modelMat,
			0.002,
			vector3d(0, 0, -1)
		);*/
		player->position.x -= MOVE_SPEED;
		gfc_matrix_make_translation(self->modelMat, player->position);
		//gfc_matrix_translate(self->modelMat, vector3d(-0.1,0,0));
		//gf3d_camera_move(vector3d(-0.4, 0, 0));


	}

	if (gfc_input_key_down("w")) {

		
		player->position.y -= MOVE_SPEED;
		gfc_matrix_make_translation(self->modelMat, player->position);

	}

	if (gfc_input_key_down("s")) {

		/*gfc_matrix_rotate(
			player->modelMat,
			player->modelMat,
			0.002,
			vector3d(0, 0, -1)
		);*/

		player->position.y += MOVE_SPEED;
		gfc_matrix_make_translation(self->modelMat, player->position);

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
}

void player_update(Entity* self) {

}