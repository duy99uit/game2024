#pragma once

//
// This file contains all IDs of game assets 
//

#define ID_TEX_JASON 0
#define ID_TEX_ENEMY 10
// #define ID_TEX_MISC 20
#define ID_TEX_MISC 20


#define OBJECT_TYPE_JASON	0
#define OBJECT_TYPE_BRICK	1
#define OBJECT_TYPE_BLACKWALKER	2
#define OBJECT_TYPE_FLYINGBOMB	3
#define OBJECT_TYPE_BOUCINGBOMB	13
#define OBJECT_TYPE_PLATFORM_WALKER	14
#define OBJECT_TYPE_BEETLEHEAD	24
#define OBJECT_TYPE_GUN_WALKER	25
#define OBJECT_TYPE_BRICK_WALKER	26
#define OBJECT_TYPE_ROTATING_GUN	27
#define OBJECT_TYPE_BEE_HEAD	28
#define OBJECT_TYPE_JELLY_FISH	29
#define OBJECT_TYPE_HEAD_BOSS	29
#define OBJECT_TYPE_BRAIN_BOSS	29
#define OBJECT_TYPE_COIN 4
#define OBJECT_TYPE_PLATFORM 5
#define OBJECT_TYPE_SOPHIA	101
#define OBJECT_TYPE_CHARACTER_BULLET	102
#define OBJECT_TYPE_POWER_P	150

#define OBJECT_TYPE_PORTAL	50


#pragma region JASON 

#define ID_SPRITE_JASON 10000
#define ID_SPRITE_JASON_BIG (ID_SPRITE_JASON + 1000)
#define ID_SPRITE_JASON_BIG_IDLE (ID_SPRITE_JASON_BIG + 100)
#define ID_SPRITE_JASON_BIG_IDLE_LEFT (ID_SPRITE_JASON_BIG_IDLE + 10)
#define ID_SPRITE_JASON_BIG_IDLE_RIGHT (ID_SPRITE_JASON_BIG_IDLE + 20)

#define ID_SPRITE_JASON_BIG_WALKING (ID_SPRITE_JASON_BIG + 200)
#define ID_SPRITE_JASON_BIG_WALKING_LEFT (ID_SPRITE_JASON_BIG_WALKING + 10)
#define ID_SPRITE_JASON_BIG_WALKING_RIGHT (ID_SPRITE_JASON_BIG_WALKING + 20)
#define ID_SPRITE_JASON_BIG_RUNNING (ID_SPRITE_JASON_BIG + 300)
#define ID_SPRITE_JASON_BIG_RUNNING_LEFT (ID_SPRITE_JASON_BIG_RUNNING + 10)
#define ID_SPRITE_JASON_BIG_RUNNING_RIGHT (ID_SPRITE_JASON_BIG_RUNNING + 20)
#define ID_SPRITE_JASON_BIG_JUMP (ID_SPRITE_JASON_BIG + 400)
#define ID_SPRITE_JASON_BIG_JUMP_WALK (ID_SPRITE_JASON_BIG_JUMP + 10)
#define ID_SPRITE_JASON_BIG_JUMP_WALK_LEFT (ID_SPRITE_JASON_BIG_JUMP_WALK + 2)
#define ID_SPRITE_JASON_BIG_JUMP_WALK_RIGHT (ID_SPRITE_JASON_BIG_JUMP_WALK + 6)
#define ID_SPRITE_JASON_BIG_JUMP_RUN (ID_SPRITE_JASON_BIG_JUMP + 20)
#define ID_SPRITE_JASON_BIG_JUMP_RUN_LEFT (ID_SPRITE_JASON_BIG_JUMP_RUN + 2)
#define ID_SPRITE_JASON_BIG_JUMP_RUN_RIGHT (ID_SPRITE_JASON_BIG_JUMP_RUN + 6)
#define ID_SPRITE_JASON_BIG_SIT (ID_SPRITE_JASON_BIG + 500)
#define ID_SPRITE_JASON_BIG_SIT_LEFT (ID_SPRITE_JASON_BIG_SIT + 10)
#define ID_SPRITE_JASON_BIG_SIT_RIGHT (ID_SPRITE_JASON_BIG_SIT + 20)
#define ID_SPRITE_JASON_BIG_BRACE (ID_SPRITE_JASON_BIG + 600)
#define ID_SPRITE_JASON_BIG_BRACE_LEFT (ID_SPRITE_JASON_BIG_BRACE + 10)
#define ID_SPRITE_JASON_BIG_BRACE_RIGHT (ID_SPRITE_JASON_BIG_BRACE + 20)

#define ID_SPRITE_JASON_DIE (ID_SPRITE_JASON + 3000)

#define ID_SPRITE_JASON_SMALL (ID_SPRITE_JASON + 2000)
#define ID_SPRITE_JASON_SMALL_IDLE (ID_SPRITE_JASON_SMALL + 100)
#define ID_SPRITE_JASON_SMALL_IDLE_LEFT (ID_SPRITE_JASON_SMALL_IDLE + 10)
#define ID_SPRITE_JASON_SMALL_IDLE_RIGHT (ID_SPRITE_JASON_SMALL_IDLE + 20)

#define ID_SPRITE_JASON_SMALL_WALKING (ID_SPRITE_JASON_SMALL + 200)
#define ID_SPRITE_JASON_SMALL_WALKING_LEFT (ID_SPRITE_JASON_SMALL_WALKING + 10)
#define ID_SPRITE_JASON_SMALL_WALKING_RIGHT (ID_SPRITE_JASON_SMALL_WALKING + 20)
#define ID_SPRITE_JASON_SMALL_RUNNING (ID_SPRITE_JASON_SMALL + 300)
#define ID_SPRITE_JASON_SMALL_RUNNING_LEFT (ID_SPRITE_JASON_SMALL_RUNNING + 10)
#define ID_SPRITE_JASON_SMALL_RUNNING_RIGHT (ID_SPRITE_JASON_SMALL_RUNNING + 20)
#define ID_SPRITE_JASON_SMALL_JUMP (ID_SPRITE_JASON_SMALL + 400)
#define ID_SPRITE_JASON_SMALL_JUMP_WALK (ID_SPRITE_JASON_SMALL_JUMP + 10)
#define ID_SPRITE_JASON_SMALL_JUMP_WALK_LEFT (ID_SPRITE_JASON_SMALL_JUMP_WALK + 2)
#define ID_SPRITE_JASON_SMALL_JUMP_WALK_RIGHT (ID_SPRITE_JASON_SMALL_JUMP_WALK + 6)
#define ID_SPRITE_JASON_SMALL_JUMP_RUN (ID_SPRITE_JASON_SMALL_JUMP + 20)
#define ID_SPRITE_JASON_SMALL_JUMP_RUN_LEFT (ID_SPRITE_JASON_SMALL_JUMP_RUN + 2)
#define ID_SPRITE_JASON_SMALL_JUMP_RUN_RIGHT (ID_SPRITE_JASON_SMALL_JUMP_RUN + 6)

#define ID_SPRITE_JASON_SMALL_SIT (ID_SPRITE_JASON_SMALL + 500)
#define ID_SPRITE_JASON_SMALL_SIT_LEFT (ID_SPRITE_JASON_SMALL_SIT + 10)
#define ID_SPRITE_JASON_SMALL_SIT_RIGHT (ID_SPRITE_JASON_SMALL_SIT + 20)

#define ID_SPRITE_JASON_SMALL_BRACE (ID_SPRITE_JASON_SMALL + 500)
#define ID_SPRITE_JASON_SMALL_BRACE_LEFT (ID_SPRITE_JASON_SMALL_BRACE + 10)
#define ID_SPRITE_JASON_SMALL_BRACE_RIGHT (ID_SPRITE_JASON_SMALL_BRACE + 20)

#pragma endregion 

#define ID_SPRITE_BRICK 20000

#define ID_SPRITE_BLACKWALKER 30000
#define ID_SPRITE_BLACKWALKER_WALK (ID_SPRITE_BLACKWALKER + 1000)
#define ID_SPRITE_BLACKWALKER_DIE (ID_SPRITE_BLACKWALKER + 2000)

#define ID_SPRITE_COIN 40000

#define ID_SPRITE_CLOUD 50000
#define ID_SPRITE_CLOUD_BEGIN (ID_SPRITE_CLOUD+1000)
#define ID_SPRITE_CLOUD_MIDDLE (ID_SPRITE_CLOUD+2000)
#define ID_SPRITE_CLOUD_END (ID_SPRITE_CLOUD+3000)