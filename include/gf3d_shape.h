#ifndef __GF3D_SHAPE_H__
#define __GF3D_SHAPE_H__

#include <SDL.h>
#include "gfc_vector.h"
#include <stdbool.h>
typedef struct
{
	Vector3D pos;
}Point;

typedef struct
{
	Vector3D start, end;
}Line;

typedef struct
{
	Vector3D pos;
	Vector3D dir;
}Ray;

typedef struct {
	
	float radius;
	Point point;
}Sphere;

typedef struct
{
	double x, y, z, w, h, d;
}Box;

typedef enum
{
	ST_Point,
	ST_Line,
	ST_Box,
	ST_Sphere,
	ST_Ray

}ShapeTypes;

typedef struct
{
	ShapeTypes type;
	union
	{
		Box b;
		Line l;
		Point p;
		Sphere sp;
		Ray ray;
	}s;

	void* data;

}Shape;

Line gf3d_line_from_vectors(Vector3D start, Vector3D end);

Shape gf3d_shape_from_line(Line line);

float radians_to_degrees(float rad);

/**
 * @brief Sets a raycast with position and direction
 * @param position the point where the ray starts
 * @param dir the direction that the ray points
 * @return the new ray
 */
Ray gf3d_ray_set(Vector3D position, Vector3D dir);

Ray FromPoints(Vector3D position, Vector3D dir);

/**
 * @brief change the position of the shape based on the movement vector
 * @param shape a pointer to the shape to move
 * @param move the amount to move the shape
 */
void gf3d_shape_move(Shape* shape, Vector3D move);

/**
 * @brief copy one shape into another
 * @param dst a pointer to the shape you want to copy into
 * @param src the shape you want to copy FROM
 */
void gf3d_shape_copy(Shape* dst, Shape src);

bool gf3d_point_in_sphere(Point point, Sphere sphere);

Point gf3d_closest_point(Sphere sphere, Point point);

float gf3d_line_length(Line line);

/**
 * @brief make a GF3D Box
 * @param x the left position of the rect
 * @param y the top position of the rect
 * @param w the width of the rect
 * @param h the height of the rect
 * @return a GF2D rect
 */
Box gf3d_box(float x, float y, float z, float w, float h, float d);

/**
 * @brief make a shape based on a rect
 * @param x the left side
 * @param y the top of the rect
 * @param w the width
 * @param h the height
 */
Shape gf3d_shape_box(float x, float y, float z, float w, float h, float d);

/**
 * @brief make a shape based on a gf2d rect
 * @param r the rect to base it on
 */
Shape gf3d_shape_from_box(Box b);

/**
 * @brief set parameters to create sphere shape
 * @param radius the radius of the sphere
 * @param pos position of the center of the sphere
 */

Shape gf3d_shape_sphere(float radius, Vector3D pos);

/**
 * @brief get the normal of the shape relative to a reference shape
 * @param s the shape to get the normal from
 * @param s2 the normal should be pointing towards this shape
 * @return an empty vector if the refPoint is in the shape, a unit vector otherwise
 */
Vector3D gf3d_shape_get_normal_for_shape(Shape s, Shape s2);

Uint8 gf3d_sphere_sphere_overlap(Sphere sphere1, Sphere sphere2);

Uint8 gf3d_sphere_overlap_poc(Sphere a, Sphere b, Vector3D* poc, Vector3D* normal);

Uint8 gf3d_shape_overlap(Shape a, Shape b);

Uint8 gf3d_shape_overlap_poc(Shape a, Shape b, Vector3D* poc, Vector3D* normal);

#ifndef gf3d_sphere_set
#define gf3d_sphere_set(sphere,r,a,b,c) (sphere.radius = r, sphere.point.pos.x = a, sphere.point.pos.y = b, sphere.point.pos.z = c)
#endif

#ifndef gf3d_box_set
#define gf3d_box_set(box,a,b,c,d,e,f) (box.x = a,box.y = b, box.z = c, box.w =d, box.h = e, box.d = f)
#endif

#ifndef gf3d_box_copy
#define gf3d_box_copy(dst,src) (dst.x = src.x,dst.y = src.y, dst.z = src.z, dst.w = src.w, dst.h = src.h, dst.d = src.d)
#endif // !gf3d_box_copy


#endif // !__GF3D_SHAPE_H__
