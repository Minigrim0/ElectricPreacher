#include "utils/utils.hpp"

#include <SDL.h>
#include <SDL_error.h>
#include <core/screen.hpp>

void save_texture(CORE::Screen* screen, SDL_Texture* texture, const char* filename){
    SDL_Texture* target = SDL_GetRenderTarget(screen->get_renderer());
    SDL_SetRenderTarget(screen->get_renderer(), texture);
    int width, height;
    SDL_QueryTexture(texture, NULL, NULL, &width, &height);
    SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
    if(surface == nullptr){
        std::cerr << "Could'nt create a surface " << SDL_GetError() << std::endl;
        return;
    }
    SDL_RenderReadPixels(screen->get_renderer(), NULL, surface->format->format, surface->pixels, surface->pitch);
    SDL_SaveBMP(surface, filename);
    SDL_FreeSurface(surface);
    SDL_SetRenderTarget(screen->get_renderer(), target);
}


SDL_Point index_to_coord(int index, int width){
    return {index % width, index / width};
}

int coord_to_index(int x, int y, int width){
    return y * width + x;
}
