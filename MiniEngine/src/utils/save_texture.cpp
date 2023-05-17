#include "utils/save_texture.hpp"

namespace MiniEngine {
    namespace Utils {
        void save_texture(Screen* screen, SDL_Texture* texture, const char* filename){
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
    }
}