#ifndef __GF3D_BODY_H__
#define __GF3D_BODY_H__

#include "gf3d_shape.h"
#include "gfc_list.h"

typedef struct Body_S
{
	int         inactive;       /**<internal use only*/
	float       gravity;        /**<the factor this body adheres to gravity*/
	Uint8       worldclip;      /**<if this body should clip the world bounds and static shapes*/
	Uint32      cliplayer;      /**<only bodies that share one or more layers will collide with each other*/
	Uint32      touchlayer;     /**<only bodies that share one or more layers will have their touch functions called*/
	Uint32      team;           /**<bodies that share a team will NOT interact*/
	Vector3D    position;       /**<position of the center of mass*/
	Vector3D    velocity;       /**<rate of change of position over time*/
	Vector3D    newvelocity;    /**<after a collision this is the new calculated velocity*/
	float       mass;           /**<used for inertia*/
	float       elasticity;     /**<how much bounce this body has*/
	Shape*		shape;			/**<which shape data will be used to collide for this body*/
	void*		data;           /**<custom data pointer*/
	int			(*touch)(struct Body_S* self, List* collision);/**< function to call when two bodies collide*/
}Body;

/**
 * @brief check if the two bodies provided are overlapping in any way
 * @param a one body
 * @param b the other body
 * @return 0 on error or no collision, 1 otherwise
 */
Uint8 gf3d_body_body_collide(Body* a, Body* b);


/**
 * @brief initializes a body to zero
 * @warning do not use this on a body in use
 */
void gf3d_body_clear(Body* body);

/**
 * @brief set all parameters for a body
 * @param body the body to set the parameters for
 * @param name the name of the body
 * @param worldclip if this body should clip the world itself
 * @param cliplayer the layer mask for bodies that clip each other
 * @param touchlayer the layer mask for what bodies to call the touch functions for
 * @param team the team
 * @param positition the position in space to be added at
 * @param velocity the velocity that the body is moving at
 * @param mass the mass of the body (for momentum purposes)
 * @param gravity the factor this body adheres to gravity
 * @param elasticity how much bounce this body has
 * @param shape a pointer to the shape data to use for the body
 * @param data any custom data you want associated with the body
 * @param bodyTouch the callback to invoke when this body touches another body
 * @param worldTouch the callback to invoke when this body touches the world
 */
void gf3d_body_set(
	Body* body,
	Uint8       worldclip,
	Uint32      cliplayer,
	Uint32      touchlayer,
	Uint32      team,
	Vector3D    position,
	Vector3D    velocity,
	float       mass,
	float       gravity,
	float       elasticity,
	Shape*		shape,
	void*		data,
	int     (*touch)(struct Body_S* self, List* collision));
/**
 * @brief apply a force to a body taking into account momentum
 * @param body the body to move
 * @param direction a unit vector for direction (Does not have to be)
 * @param force the amount of force to apply
 */
void gf3d_body_push(Body* body, Vector2D direction, float force);

/**
 * @brief get the shape, adjusted for position for the provided body
 * @param a the body to get the shape for
 * @return an empty {0} shape on error, or the body shape information otherwise
 */
Shape gf3d_body_to_shape(Body* a);

#endif // !__GF3D_BODY_H__
