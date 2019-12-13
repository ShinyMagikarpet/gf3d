#include <SDL.h>
#include "simple_logger.h"
#include "gfc_vector.h"
#include "gfc_matrix.h"

#include "gf3d_vgraphics.h"
#include "gf3d_pipeline.h"
#include "gf3d_swapchain.h"
#include "gf3d_model.h"
#include "gf3d_camera.h"
#include "gf3d_texture.h"
#include "entity.h"
#include "gfc_input.h"
#include "Player.h"
#include "ground.h"
#include "collectable.h"
#include "gfc_audio.h"
#include "gf3d_texture.h"
#include "gf3d_sprite.h"
#include "level.h"



int main(int argc,char *argv[])
{
    int done = 0;
    int a;
    Uint8 validate = 0;
    const Uint8 * keys;
    Uint32 bufferFrame = 0;
    VkCommandBuffer commandBuffer;
    Model *model;
    Matrix4 modelMat;
	Sound* music = NULL;

    for (a = 1; a < argc;a++)
    {
        if (strcmp(argv[a],"-disable_validate") == 0)
        {
            validate = 0;
        }
    }
    
	

    init_logger("gf3d.log");    
    slog("gf3d begin");
    gf3d_vgraphics_init(
        "gf3d",                 //program name
        1200,                   //screen width
        700,                    //screen height
        vector4d(0.51,0.75,1,1),//background color
        0,                      //fullscreen
        validate                //validation
    );
    
	gf3d_entity_manager_init(16);
	gfc_audio_init(256, 16, 4, 1, 1, 1);
	//music = gfc_sound_load("Sound/NJIT_Theme_Song.mp3", 1, 0);
	//gfc_sound_play(music, -1, 0.6, 1, 1);
	gf3d_texture_init(1024);

	//Entity* player = Player_New(vector3d(10, 0, 10));
	//Entity* ground = Ground_New(vector3d(-13, 0, -15), 5, "ground1");
	//Entity* ground2 = Ground_New(vector3d(10, 0, 0), 5, "ground2");
	//Collectable coin = Collectable_New(vector3d(0, 0, 3), Collectable_Yellow);
	//coin.ent->data = &coin;


	//Collectable* coin2 = Collectable_New(vector3d(3, 0, 0), Collectable_Red);

	//Collectable* coin3 = Collectable_New(vector3d(0, 0, -8), Collectable_Blue);

	LevelInfo* level = level_info_load("levels/level1.json");
	level_spawn_entities(level->spawnList);


	//gfc_matrix_translate(modelMat, vector3d(0, 0, 0));
	//player->model = gf3d_model_load("dino");
	//gfc_matrix_identity(player->modelMat);
	

	float frame = 0;
	Uint32 mouseFrame = 0;
	//Sprite* mouse = NULL;
	//mouse = gf3d_sprite_load("images/pointer.png", 32, 32, 16);
	int mousex, mousey;

	//Sprite* sprite = NULL;
	//sprite = gf3d_sprite_load("images/pink.png", 64, 64, 1);
	
	gfc_input_init("config/input.cfg");
    // main game loop
    slog("gf3d main loop begin");
    //model = gf3d_model_load_animated("Skybox", "Sky-Textures.jpg",1, 2);
    //gfc_matrix_identity(modelMat);

    /*gfc_matrix_make_translation(
            modelMat2,
            vector3d(10,0,0)
        );*/

    while(!done)
    {
		if (check_win_condition()) {
			if(strcmp(level->nextLevel, "") != 0){
				level_clear(level);
				level = level_info_load(level->nextLevel);
				level_spawn_entities(level->spawnList);
			}
			
		}
		slog(level->nextLevel);
        SDL_PumpEvents();   // update SDL's internal event structures
        keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
		SDL_GetMouseState(&mousex, &mousey);
        //update game things here

		gf3d_entity_think_all();

		if (gfc_input_key_pressed("1")) {
			//coin.ent->_inuse = 1;
			//coin2->ent->_inuse = 1;
			//coin3->ent->_inuse = 1;
		}

		frame = frame + 0.05;
		if (frame >= 1200)frame = 0;
		//mouseFrame = (mouseFrame + 1) % 16;

		

		gfc_input_update();

		gf3d_entity_update_all();
		

		//gf3d_space_update(space);

        //gf3d_vgraphics_rotate_camera(0.001);
        /*gfc_matrix_rotate(
            modelMat,
            modelMat,
            0.002,
            vector3d(1,0,0));*/
        /*gfc_matrix_rotate(
            modelMat2,
            modelMat2,
            0.002,
            vector3d(0,0,1));*/

        // configure render command for graphics command pool
        // for each mesh, get a command and configure it from the pool
        bufferFrame = gf3d_vgraphics_render_begin();
        
		gf3d_pipeline_reset_frame(gf3d_vgraphics_get_graphics_model_pipeline(), bufferFrame);
		gf3d_pipeline_reset_frame(gf3d_vgraphics_get_graphics_overlay_pipeline(), bufferFrame);

		commandBuffer = gf3d_command_rendering_begin(bufferFrame, gf3d_vgraphics_get_graphics_model_pipeline());

		//gf3d_model_draw(model, bufferFrame, commandBuffer, modelMat, 1);
		//gf3d_entity_draw(ent, bufferFrame, commandBuffer);
		gf3d_entity_draw_all(bufferFrame, commandBuffer);
                //gf3d_model_draw(ent->model,bufferFrame,commandBuffer,modelMat);
                //gf3d_model_draw(model2,bufferFrame,commandBuffer,modelMat2);

		gf3d_command_rendering_end(commandBuffer);

		commandBuffer = gf3d_command_rendering_begin(bufferFrame, gf3d_vgraphics_get_graphics_overlay_pipeline());
        
		//gf3d_sprite_draw(mouse, vector2d(mousex, mousey), mouseFrame, bufferFrame, commandBuffer);
		//gf3d_sprite_draw(sprite, vector2d(frame, 0), mouseFrame, bufferFrame, commandBuffer);
		gf3d_sprite_draw_all(bufferFrame, commandBuffer);

		gf3d_command_rendering_end(commandBuffer);

        gf3d_vgraphics_render_end(bufferFrame);

        if (keys[SDL_SCANCODE_ESCAPE])done = 1; // exit condition
    }    
    
    vkDeviceWaitIdle(gf3d_vgraphics_get_default_logical_device());    
    //cleanup
    slog("gf3d program end");
    slog_sync();
    return 0;
}

/*eol@eof*/
