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
#include "../includes/constants.h"

//Constructors
ImageSet::ImageSet()
:m_tex(nullptr),
m_width(0),
m_height(0),
m_rects()
{}

ImageSet::ImageSet(SDL_Texture* img)
:m_tex(img),
m_width(0),
m_height(0),
m_rects()
{
    SDL_QueryTexture(m_tex, NULL, NULL, &m_width, &m_height);
}

ImageSet::~ImageSet(){
    SDL_DestroyTexture(m_tex);
}

//Override
ImageSet& ImageSet::operator=(const ImageSet& set){
    m_tex = set.get_texture();

    return *this;
}

//Getters
SDL_Texture* ImageSet::get_texture() const{return m_tex;}

const SDL_Rect* ImageSet::get_sub(int x, int y) const{
    long unsigned int pos = static_cast<long unsigned int>(y*m_width/32 + x);
    if(pos > m_rects.size()) return NULL;
    return &m_rects.at(pos);
}

int ImageSet::blit_sub(Screen* sc, int img_x, int img_y, int pos_x, int pos_y) const{
    sc->blit(m_tex, get_sub(img_x, img_y), pos_x, pos_y);

    return 0;
}

int ImageSet::get_width() const{
    return m_width;
}

int ImageSet::get_height() const{
    return m_height;
}

//Setters
void ImageSet::set_image(Screen* screen, std::string image){
    screenMutex.lock();
	    m_tex = screen->load_texture(image.c_str());
    screenMutex.unlock();
    SDL_QueryTexture(m_tex, NULL, NULL, &m_width, &m_height);

    if(m_tex == NULL || m_width%32 != 0 || m_height%32 != 0)
        exit(EXIT_FAILURE);
}

//Others
int ImageSet::set_array(){
    //int width, height;

    if(m_tex == NULL) return 1;
    for(int y=0;y<m_height;y+=32){
        for(int x=0;x<m_width;x+=32){
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
