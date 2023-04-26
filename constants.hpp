#pragma once

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

#define VERSION_MAJOR 0
#define VERSION_MINOR 1
#define VERSION_PATCH 0
