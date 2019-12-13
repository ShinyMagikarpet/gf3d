#ifndef __LEVEL_H__
#define __LEVEL_H__

#include "gfc_text.h"
#include "simple_json.h"
#include "cJSON.h"

typedef struct
{
	TextLine    backgroundImage;    /**<background image for this level*/
	TextLine    backgroundMusic;    /**<background music for this level*/
	cJSON* spawnList;
	cJSON* transitionList;			/**<data for level transitions*/
	TextLine nextLevel;				/**<nextLevel filename to go to next level*/
}LevelInfo;

/**
* @brief clears the current level
*/
void level_clear();

/**
* @brief draws the level
*/
void level_draw();

/**
* @brief updates the level
*/
void level_update();

/**
 * @brief create the live level based on the provided level info
 * @param linfo the level info to create the level for
 */
void level_init(LevelInfo* linfo);

/**
 * @brief free the live level based on the provided level info
 * @param linfo the level info to free the level
 */
void level_info_free(LevelInfo* linfo);

/**
 * @brief loads level info based on contents of file
 * @param filename the file to get info from
 * @return LevelInfo the level info
 */
LevelInfo* level_info_load(char* filename);

/**
 * @brief create a new level info and populate based on parameters
 * @param backgroundImage the image file to use as the background
 * @param backgroundMusic the music the play for this level
 */
LevelInfo* level_info_create(const char* backgroundImage, const char* backgroundMusic);

void level_spawn_entities(cJSON* spawnList);

#endif // !__LEVEL_H__

