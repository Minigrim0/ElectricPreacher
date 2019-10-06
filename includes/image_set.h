#ifndef image_set_h
    #define image_set_h

/**
    name : image_set.h
    purpose : contains prototypes for the ImageSet class

    @author : minigrim0
    @version : 1.0
*/

#include <iostream>
#include <SDL2/SDL.h>

/**
    Class : ImageSet
    purpose : Image managing trough SDL_rects. Each objets represents a 'big'
    set of images, divideable into smaller bits
*/
class ImageSet{
    public:
        ImageSet();
        ~ImageSet();

    private:
        SDL_Surface* m_image;
};

#endif
