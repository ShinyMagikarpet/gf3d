#include "gf3d_config.h"
#include "simple_logger.h"
#include <stdio.h>
#include <stdlib.h>


int sj_value_as_vector2d(SJson* json, Vector2D* output)
{
	const char* text = NULL;
	float numbers[4];
	int i, count;
	SJson* value;
	if (!json)return 0;
	if (sj_is_array(json))
	{
		count = sj_array_get_count(json);
		if (count < 2)return 0;
		if (count > 2)count = 2;
		for (i = 0; i < count; i++)
		{
			value = sj_array_get_nth(json, i);
			sj_get_float_value(value, &numbers[i]);
		}
		if (output)
		{
			output->x = numbers[0];
			output->y = numbers[1];
		}
		return 1;
	}
	if (sj_is_string(json))
	{
		text = sj_get_string_value(json);
		if (sscanf(text, "%f,%f", &numbers[0], &numbers[1]) != 2)
		{
			return 0;
		}
		if (output)
		{
			output->x = numbers[0];
			output->y = numbers[1];
		}
		return 1;
	}
	return 0;
}

int sj_value_as_vector3d(SJson* json, Vector3D* output)
{
	const char* text = NULL;
	float numbers[4];
	int i, count;
	SJson* value;
	if (!json)return 0;
	if (sj_is_array(json))
	{
		count = sj_array_get_count(json);
		if (count < 3)return 0;
		if (count > 3)count = 3;
		for (i = 0; i < count; i++)
		{
			value = sj_array_get_nth(json, i);
			sj_get_float_value(value, &numbers[i]);
		}
		if (output)
		{
			output->x = numbers[0];
			output->y = numbers[1];
			output->z = numbers[2];
		}
		return 1;
	}
	if (sj_is_string(json))
	{
		text = sj_get_string_value(json);
		if (sscanf(text, "%f,%f,%f", &numbers[0], &numbers[1], &numbers[2]) != 3)
		{
			return 0;
		}
		if (output)
		{
			output->x = numbers[0];
			output->y = numbers[1];
			output->z = numbers[2];
		}
		return 1;
	}
	return 0;
}

int sj_value_as_vector4d(SJson* json, Vector4D* output)
{
	const char* text = NULL;
	float numbers[4];
	int i, count;
	SJson* value;
	if (!json)
	{
		slog("no json provided");
		return 0;
	}
	if (sj_is_array(json))
	{
		count = sj_array_get_count(json);
		if (count < 4)
		{
			slog("not enough elements in the array (%i) for a Vector4D", count);
			return 0;
		}
		if (count > 4)count = 4;
		for (i = 0; i < count; i++)
		{
			value = sj_array_get_nth(json, i);
			sj_get_float_value(value, &numbers[i]);
		}
		if (output)
		{
			output->x = numbers[0];
			output->y = numbers[1];
			output->z = numbers[2];
			output->w = numbers[3];
		}
		return 1;
	}
	if (sj_is_string(json))
	{
		text = sj_get_string_value(json);
		if (sscanf(text, "%f,%f,%f,%f", &numbers[0], &numbers[1], &numbers[2], &numbers[3]) != 4)
		{
			return 0;
		}
		if (output)
		{
			output->x = numbers[0];
			output->y = numbers[1];
			output->z = numbers[2];
			output->w = numbers[3];
		}
		return 1;
	}
	slog("json is not an array or string");
	sj_echo(json);
	return 0;
}

char* read_file_for_cjson(char* filename) {

	FILE* f = fopen(filename, "rb");
	fseek(f, 0, SEEK_END);
	long fsize = ftell(f);
	fseek(f, 0, SEEK_SET);  /* same as rewind(f); */

	char* string = malloc(fsize + 1);
	fread(string, 1, fsize, f);
	fclose(f);

	string[fsize] = 0;
	return string;
}

Vector3D cjson_value_as_vector3d(cJSON* json) {

	if (!json) {
		slog("No json provided");
		return vector3d(0, 0, 0);
	}

	Vector3D vec3 = vector3d(0,0,0);
	int i = 0;
	cJSON* vec = NULL;
	cJSON_ArrayForEach(vec, json) {
		switch (i)
		{
		case 0:
			vec3.x = vec->valuedouble;
			break;
		case 1:
			vec3.y = vec->valuedouble;
			break;
		case 2:
			vec3.z = vec->valuedouble;
			break;
		default:
			break;
		}
		i++;
	}

	return vec3;
}

/*eol@eof*/