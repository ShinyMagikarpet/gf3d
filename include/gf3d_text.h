#ifndef __GF3D_TEXT__
#define __GF3D_TEXT__

#include "gfc_text.h"
#include "gf3d_vgraphics.h"
#include <SDL_ttf.h>
#include "gf3d_texture.h"
#include "gf3d_sprite.h"

typedef struct {
	Uint8                       _inuse;
	SDL_Surface*				surface;
	Texture*					texture;
	TextLine                    filename;               /**<Font filename*/
	TextLine					text;
	Vector2D					position;				/**<Position of sprite in screen space*/
	Sprite*						sprite;
}TextBox;

void text_manager_init(Uint32 text_max);

void text_manager_close();

void gf3d_textbox_free(TextBox* textbox);

void gf3d_textbox_free_all();

TextBox* gf3d_text_new(char* fontFile, const char* text);

void gf3d_text_create(TextBox* textbox);

void gf3d_draw_text(Uint32 bufferFrame, VkCommandBuffer commandBuffer);



#endif // !__GF3D_TEXT__
