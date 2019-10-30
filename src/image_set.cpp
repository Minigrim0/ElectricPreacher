/**
    name : image_set.cpp
    purpose : contains the source code for the ImageSet class

    @author : minigrim0
    @version : 1.1
*/

#include <iostream>
#include <SDL2/SDL.h>

#include "../includes/image_set.h"
#include "../includes/screen.h"

//Constructors
ImageSet::ImageSet()
:m_image(nullptr),
m_rects()
{}

ImageSet::ImageSet(const ImageSet& set)
:m_image(set.get_image()),
m_rects()
{
    set_array();
}

ImageSet::ImageSet(SDL_Surface* img)
:m_image(img),
m_rects()
{}

ImageSet::~ImageSet(){
    SDL_FreeSurface(m_image);
}

//Override
ImageSet& ImageSet::operator=(const ImageSet& set){
    m_image = set.get_image();

    return *this;
}

//Getters
SDL_Surface* ImageSet::get_image() const{return m_image;}

const SDL_Rect* ImageSet::get_sub(int x, int y) const{
    long unsigned int pos = static_cast<long unsigned int>(y*m_image->w/32 + x);
    if(pos > m_rects.size()) return NULL;
    return &m_rects.at(pos);
}

//Setters
void ImageSet::set_image(Screen* screen, std::string image){
	m_image = screen->load_image(image.c_str());
    if(m_image == NULL || m_image->w%32 != 0 || m_image->h%32 != 0)
        exit(EXIT_FAILURE);
}

//Others
int ImageSet::set_array(){
    if(m_image == NULL) return 1;
    for(int y=0;y<m_image->h;y+=32){
        for(int x=0;x<m_image->w;x+=32){
            SDL_Rect tmp_rect;
            tmp_rect.x = x;
            tmp_rect.y = y;
            tmp_rect.w = 32;
            tmp_rect.h = 32;

            m_rects.push_back(tmp_rect);
        }
    }
    return 0;
}
