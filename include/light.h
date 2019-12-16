#ifndef __LIGHT_H__
#define __LIGHT_H__
#include "gfc_vector.h"

typedef struct {
	Vector3D dir;
	Vector3D position;
	Vector4D color;
	float radius;
	float range;
	float intensity;
	float maxIntensity;
	Uint32 isPoint;
	Uint32 _inuse;
}Light;

extern Uint32 g_gradient;

void light_init(Uint32 max_lights);

void close_lights();

void light_free(Light* light);

Light* new_light();

Light* create_light(Vector3D direction, Vector4D color, float intensity, float maxIntensity);

Light* create_point_light(Vector3D position, Vector4D color, float radius, float range, float intensity, float maxIntensity);

Light* get_light(int index);


#endif // !__LIGHT_H__
