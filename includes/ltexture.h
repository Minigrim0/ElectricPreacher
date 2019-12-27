#include <iostream>

#include <SDL2/SDL.h>
#include "screen.h"

class LTexture{
	public:
		//Initializes variables
		LTexture();

		//Deallocates memory
		~LTexture();

		//Loads image at specified path
		bool loadFromFile(Screen*, std::string path);

		//Creates image from font string
		bool loadFromRenderedText(Screen*, std::string textureText, SDL_Color textColor);

		//Deallocates texture
		void free_texture();

		//Set color modulation
		void setColor(Uint8 red, Uint8 green, Uint8 blue);

		//Set blending
		void setBlendMode(SDL_BlendMode blending);

		//Set alpha modulation
		void setAlpha(Uint8 alpha);

		//Renders texture at given point
		void render(Screen*, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

		//Gets image dimensions
		int getWidth();
		int getHeight();

	private:
		//The actual hardware texture
		SDL_Texture* m_texture;

		//Image dimensions
		int m_width;
		int m_height;
};
