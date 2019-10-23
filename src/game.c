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
#include "gf3d_space.h"


int main(int argc,char *argv[])
{
    int done = 0;
    int a;
    Uint8 validate = 0;
    const Uint8 * keys;
    Uint32 bufferFrame = 0;
    VkCommandBuffer commandBuffer;
    //Model *model;
    Matrix4 modelMat;
    //Model *model2;
    //Matrix4 modelMat2;

	//Not sure if this is working
	Sphere sphere;
	gf3d_sphere_set(sphere, 1, 0, 0, 0);

	Sphere sphere2;
	gf3d_sphere_set(sphere, 1, 2, 0, 0);

	Space* space = gf2d_space_new_full(
		3,
		0.1,
		vector3d(0, 0.1, 0),
		1,
		20

	);

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
	
	Entity* ent = gf3d_entity_new();
	ent->model = gf3d_model_load_animated("sphere_anim", 1, 3);	
	gfc_matrix_identity(ent->modelMat);
	gfc_matrix_translate(ent->modelMat, vector3d(2, 0, 0));
	ent->frame = 1;
	ent->position = vector3d(2, 0, 0);
	ent->shape = gf3d_shape_sphere(1, vector3d(2, 0, 0));
	ent->position = ent->shape.s.s.point.pos;
	gf3d_body_set(
		&ent->body,
		0,
		0,
		0,
		0,
		ent->position,
		vector3d(0, 0, 0),
		1,
		0,
		0,
		&ent->shape,
		NULL,
		NULL);

	Entity *player = Player_New();


	//gfc_matrix_translate(modelMat, vector3d(0, 0, 0));
	//player->model = gf3d_model_load("dino");
	//gfc_matrix_identity(player->modelMat);
	
	gfc_input_init("config/input.cfg");
    // main game loop
    slog("gf3d main loop begin");
    //model = gf3d_model_load("dino");
    //gfc_matrix_identity(modelMat);
    //model2 = gf3d_model_load("dino");
    //gfc_matrix_identity(modelMat2);
    /*gfc_matrix_make_translation(
            modelMat2,
            vector3d(10,0,0)
        );*/
    while(!done)
    {
        SDL_PumpEvents();   // update SDL's internal event structures
        keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
        //update game things here

		gf3d_entity_think_all();

		gfc_input_update();

		gf3d_entity_update_all();
		
		gf3d_space_update(space);
		//slog("Entity name is %s", player->name);

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
        gf3d_pipeline_reset_frame(gf3d_vgraphics_get_graphics_pipeline(),bufferFrame);
        commandBuffer = gf3d_command_rendering_begin(bufferFrame);
		
			//gf3d_model_draw(player->model, bufferFrame, commandBuffer, player->modelMat);
			//gf3d_entity_draw(ent, bufferFrame, commandBuffer);
		gf3d_entity_draw_all(bufferFrame, commandBuffer);
                //gf3d_model_draw(ent->model,bufferFrame,commandBuffer,modelMat);
                //gf3d_model_draw(model2,bufferFrame,commandBuffer,modelMat2);

		
                
            gf3d_command_rendering_end(commandBuffer);
            
        gf3d_vgraphics_render_end(bufferFrame);

        if (keys[SDL_SCANCODE_ESCAPE])done = 1; // exit condition
    }    
    
    vkDeviceWaitIdle(gf3d_vgraphics_get_default_logical_device());    
    //cleanup
    slog("gf3d program end");
	gf3d_space_free(space);
    slog_sync();
    return 0;
}

/*eol@eof*/
