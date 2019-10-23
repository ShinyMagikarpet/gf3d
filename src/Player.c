#include "Player.h"
#include "gfc_input.h"
#include "gf3d_camera.h"
#include "gf3d_space.h"
#include "simple_logger.h"

#define MOVE_SPEED 0.02
static Entity* player = NULL;

void player_think(Entity* self);
void player_update(Entity* self);


Entity* Player_New() {

	player = gf3d_entity_new();
	player->tag = "player";
	//player->model = gf3d_model_load("sphere");
	player->model = gf3d_model_load_animated("sphere_anim", 1, 23);
	gfc_matrix_identity(player->modelMat);

	player->position = vector3d(0, 0, 0);
	player->shape = gf3d_shape_sphere(1, player->position);
	gf3d_body_set(
		&player->body,
		0,
		0,
		0,
		1,
		player->position,
		vector3d(0, 0, 0),
		1,
		0,
		0,
		&player->shape,
		NULL,
		NULL);
	player->think = player_think;
	player->update = player_update;
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

		player->velocity.x = MOVE_SPEED;
		//gf3d_entity_move(self, vector3d(MOVE_SPEED, 0, 0));

	}

	if (gfc_input_key_down("d")) {

		/*gfc_matrix_rotate(
			player->modelMat,
			player->modelMat,
			0.002,
			vector3d(0, 0, -1)
		);*/
		player->velocity.x = -MOVE_SPEED;
		//gf3d_entity_move(self, vector3d(-MOVE_SPEED, 0, 0));

	}

	if (gfc_input_key_down("w")) {

		player->velocity.y = -MOVE_SPEED;
		//gf3d_entity_move(self, vector3d(0, -MOVE_SPEED, 0));

	}

	if (gfc_input_key_down("s")) {

		/*gfc_matrix_rotate(
			player->modelMat,
			player->modelMat,
			0.002,
			vector3d(0, 0, -1)
		);*/

		player->velocity.y = MOVE_SPEED;

		//gf3d_entity_move(self, vector3d(0, MOVE_SPEED, 0));

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

	if (gfc_input_key_down(" ")) {
		player->frame += 1;
		if (player->frame > 19) {
			player->frame = 19;
		}
	}

	if (gfc_input_key_released(" ")) {
		player->frame = 0;
	}
	
	//slog("total entities %i", get_entity_size());
	//gf3d_entity_move(self, vector3d(0, 0, -9));
	
	//slog("player frame %i", player->frame);
}

void player_update(Entity* self) {

	Vector3D oldPos = self->shape.s.s.point.pos;

	//gf3d_entity_move(self, self->velocity);
	
	self->shape.s.s.point.pos.x += self->velocity.x;
	self->shape.s.s.point.pos.y += self->velocity.y;
	self->shape.s.s.point.pos.z += self->velocity.z;

	for (int i = 0; i < get_entity_size(); i++) {

		Body* ent_body = get_entity_bodies(i);

		if (ent_body == &player->body) {
			continue;
		}

		if (gf3d_body_body_collide(&player->body, ent_body)) {
			//ent->_inuse = 0;
			slog("TOUCHING");
			//gf3d_entity_move(self, self->velocity);
			//player->position = oldPos;
			self->shape.s.s.point.pos = oldPos;
			slog("%f, %f, %f", oldPos.x, oldPos.y, oldPos.z);
		}
		else {
			//slog("These sphere aren't touching");
			gf3d_entity_move(self, self->velocity);
		}
	}
	//player->body.position = player->position;
	
	player->velocity = vector3d(0, 0, 0);
}