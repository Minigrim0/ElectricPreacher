#ifndef constants_h
    #define constants_h

//Map
#define CHUNK_SIZE 20

//Screen
#define SCREEN_X 1440
#define SCREEN_Y 900

#define EDITOR_SCREEN_X 1440
#define EDITOR_SCREEN_Y 900

//Directions
enum Directions
{
    DIRECTION_UP,
    DIRECTION_DOWN,
    DIRECTION_LEFT,
    DIRECTION_RIGHT,
};

//SceneryElement
#define TYPE_SIGN  1
#define TYPE_LEVER 2
#define TYPE_TABLE 3
#define TYPE_ITEM  4

// DEBUG
#define DEBUG true

#endif
