#ifndef constants_h
    #define constants_h

#include <iostream>

//Map
#define CHUNK_SIZE 16

//Screen
#define SCREEN_X 1920
#define SCREEN_Y 1080

//Directions
enum Directions
{
    DIRECTION_UP,
    DIRECTION_DOWN,
    DIRECTION_LEFT,
    DIRECTION_RIGHT,
};

//SceneryElement
enum ElementType
{
    TYPE_SIGN,
    TYPE_LEVER,
    TYPE_TABLE,
    TYPE_ITEM,
};

#define VERSION_MAJOR @Tutorial_VERSION_MAJOR@
#define VERSION_MINOR @Tutorial_VERSION_MINOR@

#endif
