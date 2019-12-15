#include "light.h"
#include "simple_logger.h"

typedef struct {
	Uint32 max_size;
	Light* light_list;
}LightManager;

static LightManager light_manager = { 0 };

void close_lights() {
	if (light_manager.light_list != NULL)
	{
		free(light_manager.light_list);
	}
	memset(&light_manager, 0, sizeof(LightManager));
}

void light_init(Uint32 max_lights) {
	light_manager.light_list = (Light*)gfc_allocate_array(sizeof(Light), max_lights);
	if (!light_manager.light_list)
	{
		slog("failed to allocate light list");
		return;
	}
	light_manager.max_size = max_lights;
	slog("Light system initialized with size of %i", light_manager.max_size);
	atexit(close_lights);
}

void light_free(Light* light) {

	if (light != NULL) {
		free(light);
	}
}

Light* new_light() {
	int i;
	for (i = 0; i < light_manager.max_size; i++) {
		if (light_manager.light_list[i]._inuse)continue;
		memset(&light_manager.light_list[i], 0, sizeof(Light));
		light_manager.light_list[i]._inuse = 1;
		return &light_manager.light_list[i];
	}
	slog("Failed to allocate new light: manager too full");
	return NULL;
}

Light* create_light(Vector3D direction, float intensity, float maxIntensity) {
	Light* light = NULL;
	light = new_light();
	if (!light) {
		slog("Failed to create light");
	}
	vector3d_copy(light->dir, direction);
	light->intensity = intensity;
	light->maxIntensity = maxIntensity;
	return light;
}

Light* get_light(int index) {
	return &light_manager.light_list[index];
}