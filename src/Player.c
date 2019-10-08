#include "Player.h"
#include "gfc_input.h"

static Entity* player = NULL;

void player_think(Entity* self);
void player_update(Entity* self);


Entity* Player_New() {

	player = gf3d_entity_new();
	player->model = gf3d_model_load("dino");
	gfc_matrix_identity(player->modelMat);
	
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
		gfc_matrix_translate(self->modelMat, vector3d(.01, 0, 0));


	}

	if (gfc_input_key_down("d")) {

		/*gfc_matrix_rotate(
			player->modelMat,
			player->modelMat,
			0.002,
			vector3d(0, 0, -1)
		);*/

		gfc_matrix_translate(self->modelMat, vector3d(-0.01, 0, 0));


	}

	if (gfc_input_key_down("w")) {

		/*gfc_matrix_rotate(
			player->modelMat,
			player->modelMat,
			0.002,
			vector3d(0, 0, -1)
		);*/
		gfc_matrix_translate(self->modelMat, vector3d(0, -0.01, 0));


	}

	if (gfc_input_key_down("s")) {

		/*gfc_matrix_rotate(
			player->modelMat,
			player->modelMat,
			0.002,
			vector3d(0, 0, -1)
		);*/

		gfc_matrix_translate(self->modelMat, vector3d(0, 0.01, 0));


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