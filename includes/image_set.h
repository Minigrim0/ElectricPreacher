#ifndef image_set_h
    #define image_set_h

/**
    name : image_set.h
    purpose : Image managing trough SDL_rects. Each objets represents a 'big'
    set of images, divideable into smaller bits

    @author : minigrim0
    @version : 1.1
*/

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>

#include "screen.h"

class ImageSet{
    public:
        //Constructors
        ImageSet();
        ImageSet(const ImageSet&);
        ImageSet(SDL_Texture*);
        ~ImageSet();

        //Override
        ImageSet& operator=(const ImageSet&);

        //Getters
        SDL_Texture* get_texture() const;
        const SDL_Rect* get_sub(int, int) const;
        int get_width() const;
        int get_height() const;

        //Setters
        void set_image(Screen* screen, std::string);

        //Others
        int set_array();

    private:
        SDL_Texture* m_tex;
        int m_width, m_height;

        std::vector<SDL_Rect> m_rects;
};

#endif
