#ifndef ltexture_h
	#define ltexture_h

/**
    name : ltexture.h
    purpose : Temporary class handling texture managing

    @author : minigrim0
    @version : 1.1
*/

#include <iostream>

#include <SDL2/SDL.h>
#include "screen.h"

class LTexture{
	public:
		LTexture();
		LTexture(const LTexture&);

		~LTexture();

		LTexture& operator=(const LTexture&);

		bool loadFromFile(Screen*, std::string path);

		bool loadFromRenderedText(Screen*, std::string textureText, SDL_Color textColor);

		void free_texture();

		void setColor(Uint8 red, Uint8 green, Uint8 blue);

		void setBlendMode(SDL_BlendMode blending);

		void setAlpha(Uint8 alpha);

		void render(Screen*, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

		int getWidth();
		int getHeight();

	private:
		SDL_Texture* m_texture;

		int m_width;
		int m_height;
};

#endif
