#include "gf3d_shape.h"
#include "simple_logger.h"


void gf3d_shape_move(Shape* shape, Vector3D move) {

	if (!shape)return;
	shape->s.s.point.pos.x += move.x;
	shape->s.s.point.pos.y += move.y;
	shape->s.s.point.pos.z += move.z;
}

void gf3d_shape_copy(Shape* dst, Shape src) {
	
	if (!dst)return;
	memcpy(dst, &src, sizeof(Shape));
}

float gf3d_line_length(Line line) {
	
	return vector3d_magnitude_between(line.start.pos, line.end.pos);
}

bool gf3d_point_in_sphere(Point point, Sphere sphere) {

	Vector3D temp;
	vector3d_sub(temp, point.pos, sphere.point.pos);
	float magSq = vector3d_magnitude_squared(temp);
	slog("magSq = %f", magSq);
	float radSq = sphere.radius * sphere.radius;
	slog("radSq = %f", radSq);

	return magSq < radSq;
}

Point gf3d_closest_point(Sphere sphere, Point point) {
	Point sphereToPoint, temp;
	vector3d_sub(temp.pos, point.pos, sphere.point.pos);
	vector3d_normalize(&temp);

	sphereToPoint.pos.x = temp.pos.x * sphere.radius;
	sphereToPoint.pos.y = temp.pos.y * sphere.radius;
	sphereToPoint.pos.z = temp.pos.z * sphere.radius;

	vector3d_add(sphereToPoint.pos, sphereToPoint.pos, sphere.point.pos);
	return sphereToPoint;
}

Box gf3d_box(float x, float y, float z, float w, float h, float d) {

	Box box;
	gf3d_box_set(box, x, y, z, w, h, d);
	return box;
}

Shape gf3d_shape_box(float x, float y, float z, float w, float h, float d) {

}

Shape gf3d_shape_from_box(Box b) {

}

Shape gf3d_shape_sphere(float radius, Vector3D pos) {

	Shape shape;
	shape.type = ST_Sphere;
	shape.s.s.radius = radius;
	shape.s.s.point.pos = pos;
	return shape;
}

bool gf3d_sphere_sphere_overlap(Sphere sphere1, Sphere sphere2) {

	float radiiSum = sphere1.radius + sphere2.radius;
	Vector3D subtractVec;
	vector3d_sub(subtractVec, sphere1.point.pos, sphere2.point.pos);
	float sqDistance = vector3d_magnitude_squared(subtractVec);
	return sqDistance < radiiSum * radiiSum;
}

Uint8 gf3d_sphere_overlap_poc(Sphere a, Sphere b, Vector3D* poc, Vector3D* normal)
{
	Vector3D v;
	vector3d_set(v, a.point.pos.x - b.point.pos.x, a.point.pos.x - b.point.pos.y, a.point.pos.z - b.point.pos.z);
	if (vector3d_magnitude_compare(v, a.radius + b.radius) <= 0)
	{
		if (poc)
		{
			vector3d_normalize(&v);
			if (normal)
			{
				normal->x = v.x;
				normal->y = v.y;
				normal->z = v.z;
			}
			vector3d_scale(v, v, a.radius);
			poc->x = a.point.pos.x + v.x;
			poc->y = a.point.pos.y + v.y;
			poc->z = a.point.pos.z + v.z;

		}
		return 1;
	}
	return 0;
}


Uint8 gf3d_shape_overlap_poc(Shape a, Shape b, Vector3D* poc, Vector3D* normal)
{
	switch (a.type)
	{
	case ST_Sphere:
		switch (b.type)
		{
		case ST_Sphere:
			return gf3d_sphere_overlap_poc(a.s.s, b.s.s, poc, normal);
		}
	}
	return 0;
}

Uint8 gf3d_shape_overlap(Shape a, Shape b)
{
	return gf3d_shape_overlap_poc(a, b, NULL, NULL);
}
