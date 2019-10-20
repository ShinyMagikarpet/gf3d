#ifndef __GF3D_SPACE_H__
#define __GF3D_SPACE_H__

#include "gfc_matrix.h"
#include "gfc_list.h"
#include "gf3d_shape.h"

typedef struct Space_S{
	List* dynamicBodyList;       /**<list of bodies in the space*/
	List* staticShapes;   /**<list of shapes that will collide that do not move*/
	int         precision;      /**<number of backoff attempts before giving up*/
	Box			bounds;         /**<absolute bounds of the space*/
	float       timeStep;       /**<how much each iteration of the simulation progresses time by*/
	Vector3D    gravity;        /**<global gravity pull direction*/
	float       dampening;      /**<rate of movement degrade  ambient frictions*/
	float       slop;           /**<how much to correct for body overlap*/
	Uint32      idpool;
}Space;

/**
*@brief create a new space
*@return NULL on error or a new empty space
*/
Space * gf2d_space_new();

/**
 * @brief create a new space and set some defaults
 * @param precision number of retry attempts when movement collides
 * @param bounds the absolute bounds of the space
 * @param timeStep this should be fraction that can add up to 1.  ie: 0.1 or 0.01, etc
 * @param gravity the direction that gravity pulls
 * @param dampening the rate of all movemement decay
 * @param slop how much to correct for body overlap
 */
Space* gf2d_space_new_full(
	int         precision,
	Box        bounds,
	float       timeStep,
	Vector3D    gravity,
	float       dampening,
	float       slop);

/**
 * @brief cleans up a space
 */
void gf3d_space_free(Space* space);

/**
*	@brier updates the physics space
*/
void gf3d_space_update(Space* space);

void gf3d_space_step(Space* space, float t);

/**
 * @brief add a statuc shape to the space
 * @note the shape parameters need to be in absolute space, not relative to any body
 * @param space the space to add to
 * @param shape the shape to add.
 */
void gf3d_space_add_static_shape(Space* space, Shape shape);

#endif // !__GF3D_SPACE_H__
