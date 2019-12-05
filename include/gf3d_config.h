#ifndef __GF3D_CONFIG_H__
#define __GF3D_CONFIG_H__

#include "simple_json.h"
#include "gfc_vector.h"
#include "cJSON.h"

int sj_value_as_vector2d(SJson* json, Vector2D* output);
int sj_value_as_vector3d(SJson* json, Vector3D* output);
int sj_value_as_vector4d(SJson* json, Vector4D* output);

char* read_file_for_cjson(char* filename);
Vector3D cjson_value_as_vector3d(cJSON* json);


#endif // !__GF3D_CONFIG_H__

