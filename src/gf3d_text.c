#include "gf3d_text.h"
#include "simple_logger.h"
#include "SDL.h"
#include "gf3d_sprite.h"

typedef struct
{
	Matrix4     model;          /**<how the sprite should be transformed each frame*/
	Vector2D    frame_offset;   /**<where to sample the texture from this frame*/
}TextUBO;

typedef struct
{
	Vector2D vertex;
	Vector2D texel;
}TextVertex;

typedef struct
{
	Uint32  verts[3];
}TextFace;

typedef struct {

	TextBox*	text_list;
	Uint32		text_max;

}TextManager;

static TextManager text_manager = { 0 };

Texture* surface_to_texture(SDL_Surface* surface, const char* text);
Sprite* create_text_sprite(Texture* texture);


void text_manager_close() {
	if (text_manager.text_list != NULL)
	{
		free(text_manager.text_list);
	}
	memset(&text_manager, 0, sizeof(TextManager));
}

void text_manager_init(Uint32 text_max) {

	text_manager.text_list = (TextBox*)gfc_allocate_array(sizeof(TextBox), text_max);
	if (!text_manager.text_list)
	{
		slog("failed to allocate text list");
		return;
	}
	text_manager.text_max = text_max;
	slog("Text system initialized with size of %i", text_manager.text_max);
	atexit(text_manager_close);
}


void gf3d_textbox_free(TextBox* textbox) {

	if (!textbox)
	{
		slog("textbox pointer is not valid");
		return;
	}
	textbox->_inuse = 0;
	memset(textbox, 0, sizeof(TextBox));
}

void gf3d_textbox_free_all() {
	int i;
	for (i = 0; i < text_manager.text_max; i++) {
		gf3d_textbox_free(&text_manager.text_list[i]);
	}
}

Texture* surface_to_texture(SDL_Surface* surface, const char* text) {

	
}

Sprite* create_text_sprite(Texture* texture) {
	Sprite* sprite;
	sprite = gf3d_sprite_new();
	if (!sprite)
	{
		return NULL;
	}
	sprite->texture = texture;
	if (!sprite->texture)
	{
		slog("gf3d_sprite_load: failed to load texture for text sprite");
		gf3d_sprite_free(sprite);
		return NULL;
	}

	gf3d_sprite_create_vertex_buffer(sprite);
	return sprite;
}

void gf3d_text_create(TextBox* textbox) {
	SDL_Surface* surface = NULL;
	Texture* texture = NULL;
	SDL_Color color = { 255, 255, 255 };
	TTF_Init();
	TTF_Font* font = TTF_OpenFont(textbox->filename, 12);
	surface = TTF_RenderUTF8_Blended(font, textbox->text, color);
	if (!surface) {
		slog("Could not make surface for textbox");
	}
	textbox->surface = surface;
	texture = surface_to_texture(textbox->surface, textbox->text);
	if (!texture) {
		slog("Could not make surface for texture");
	}
	textbox->texture = texture;
	textbox->sprite = gf3d_sprite_load("", 128, 64, 1, 1, textbox->texture);
	if (!textbox->sprite) {
		slog("failed to create sprite for textbox");
	}
	TTF_CloseFont(font);
	TTF_Quit();
}

TextBox* gf3d_text_new(char* fontFile, const char* text) {
	int i;
	for (i = 0; i < text_manager.text_max; i++) {
		if (text_manager.text_list[i]._inuse)continue;
		memset(&text_manager.text_list[i], 0, sizeof(TextBox));
		gfc_line_cpy(&text_manager.text_list[i].filename, fontFile);
		gfc_line_cpy(&text_manager.text_list[i].text, text);
		gf3d_text_create(&text_manager.text_list[i]);
		text_manager.text_list[i]._inuse = 1;
		slog("Generated new textbox");
		return &text_manager.text_list[i];
	}
	slog("request for entity failed: all full up");
	return NULL;
}

void gf3d_draw_text(Uint32 bufferFrame, VkCommandBuffer commandBuffer) {

}