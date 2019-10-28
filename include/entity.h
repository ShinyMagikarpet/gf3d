#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "gf3d_model.h"
#include "gf3d_space.h"

#define GRAVITY 0.1f

typedef enum
{
	ES_Idle = 0,
	ES_Dying = 1,
	ES_Dead = 2
}EntityState;

typedef struct Entity_S
{
	char* name;
	Uint8            _inuse;         /**<flag to keep track if this isntance is in use and should not be reassigned*/
	Uint8			_ID;
	char*			 tag;
	Model*			 model;          /**<the 3d model for this entity*/
	Uint32			 frame;
	Matrix4			 modelMat;
	Body			 body;
	Shape			 shape;
	Ray				 rayf;			 /**<forward direction for entity*/
	Ray				 rayd;			 /**<downward direction for entity*/
	Vector3D         position;       /**<position of the entity in 3d space*/
	Vector3D         velocity;       /**<velocity of the entity in 3d space*/
	Vector3D         gravity;		/**<acceleration of the entity in 3d space*/
	Vector3D         rotation;       /**<yaw, pitch, and roll of the entity*/
	Vector3D         scale;          /**<*please default to 1,1,1*/
	EntityState      state;          /**<current state of the entity*/
	float			jumpTime;		 /**<Time to be in air*/
	Uint8			grounded;
	void (*think)(struct Entity_S* self);   /**<function called on entity think*/
	void (*update)(struct Entity_S* self);   /**<function called on entity update*/
	void (*touch)(struct Entity_S* self, struct Entity_S* other);   /**<function called on entity think*/
	void(*draw)(struct Entity_S* self, Uint32 bufferFrame, VkCommandBuffer commandBuffer);


	void* data;                     /**<additional entity specific data*/

}Entity;

/**
 * @brief initializes the entity subsystem
 * @param entity_max maximum number of simultaneous entities you wish to support
 */
void gf3d_entity_manager_init(Uint32 entity_max);

/**
 * @brief get an empty entity from the system
 * @return NULL on out of space or a pointer to an entity otherwise
 */
Entity* gf3d_entity_new();

/**
 * @brief free an active entity
 * @param self the entity to free
 */
void    gf3d_entity_free(Entity* self);

/**
*@brief draw entity
*@param self the entity to draw
*@param bufferFrame
*@param commandBuffer
*/

void gf3d_entity_draw(Entity* self, Uint32 bufferFrame, VkCommandBuffer commandBuffer);

/**
* @brief draw all entities
*/
void gf3d_entity_draw_all(Uint32 bufferFrame, VkCommandBuffer commandBuffer);

void gf3d_entity_think(Entity* self);

void gf3d_entity_think_all();

void gf3d_entity_update(Entity* self);

void gf3d_entity_update_all();

void gf3d_entity_move(Entity* ent, Vector3D dir);

Body* get_entity_bodies(int i);

Uint32 get_entity_size();

void slog_entity_positions();

void slog_entity_names();

Entity* entity_near();

#endif // !__ENTITY_H__

