/**
    name : image_set.cpp
    purpose : contains the source code for the ImageSet class

    @author : minigrim0
    @version : 1.1
*/

#include <iostream>
#include <SDL2/SDL.h>

#include "../includes/image_set.h"

//Constructors
ImageSet::ImageSet(): m_image(NULL){}

ImageSet::ImageSet(const ImageSet& set): m_image(set.get_image()){}

ImageSet::ImageSet(SDL_Surface* img): m_image(NULL){
    set_image(img);
}

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
    int pos = (y*m_image->w/32 + x);
    if(pos > m_rects.size()) return NULL;
    return &m_rects.at(pos);
}

//Setters
int ImageSet::set_image(SDL_Surface* image){
    if(image == NULL || image->w%32 != 0 || image->h%32 != 0)
        return 1;

    m_image = image;
    return 0;
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
