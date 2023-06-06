#include "utils/save_texture.hpp"

#include "core/log.hpp"

namespace MiniEngine {
    namespace Utils {
        void save_texture(Screen* screen, SDL_Texture* texture, const char* filename){
            SDL_Texture* target = SDL_GetRenderTarget(screen->get_renderer());
            SDL_SetRenderTarget(screen->get_renderer(), texture);
            int width, height;
            SDL_QueryTexture(texture, NULL, NULL, &width, &height);
            ME_CORE_TRACE("> Save Texture : {0}x{1}", width, height);
            SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
            if(surface == nullptr){
                ME_CORE_ERROR("Could'nt create a surface {0}", SDL_GetError());
                return;
            }
            SDL_RenderReadPixels(screen->get_renderer(), NULL, surface->format->format, surface->pixels, surface->pitch);
            SDL_SaveBMP(surface, filename);
            SDL_FreeSurface(surface);
            SDL_SetRenderTarget(screen->get_renderer(), target);
        }

        void save_texture(SDL_Surface* surf, const char* filename){
            SDL_SaveBMP(surf, filename);
        }
    }
}
