#ifndef __GF3D_SHAPE_H__
#define __GF3D_SHAPE_H__

#include <SDL.h>
#include "gfc_vector.h"
typedef struct
{
	Vector3D p;
}Point;

typedef struct
{
	Point start, end;
}Line;

typedef struct {
	
	double r;
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

}ShapeTypes;

typedef struct
{
	ShapeTypes type;
	union
	{
		Box b;
		Line e;
		Point p;
	}s;

}Shape;

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
 * @brief set all parameters of a GF2D rect at once
 * @param box the box to set
 * @param a the x component
 * @param b the y component
 * @param c the z component
 * @param d the width
 * @param e the height
 * @param f the depth
 */

#ifndef gf3d_box_set
#define gf3d_box_set(box,a,b,c,d,e,f) (box.x = a,box.y = b, box.z = c, box.w =d, box.h = e, box.d = f)
#endif

#ifndef gf3d_box_copy
#define gf3d_box_copy(dst,src) (dst.x = src.x,dst.y = src.y, dst.z = src.z, dst.w = src.w, dst.h = src.h, dst.d = src.d)
#endif // !gf3d_box_copy


#endif // !__GF3D_SHAPE_H__
