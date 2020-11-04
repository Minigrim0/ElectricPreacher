#ifndef constants_h
    #define constants_h

#include <iostream>

//Map
#define CHUNK_SIZE 20

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

#define VERSION 0
#define SUBVERSION 1
#define SUBSUBVERSION 1

#endif
