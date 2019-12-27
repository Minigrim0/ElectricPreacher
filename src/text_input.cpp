#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../includes/text_input.h"
#include "../includes/constants.h"

TextInput::TextInput()
:m_tex(nullptr),
m_background_image(nullptr),
m_init_size(),
m_screen_pos_size(nullptr),
m_current_input("aeeae"),
m_cursor_pos(0),
m_selection_len(0),
m_is_active(false)
{
    if(DEBUG) std::cout << __PRETTY_FUNCTION__ << "> Creating new TextInput" << std::endl;
    m_init_size = static_cast<SDL_Rect*>(malloc(sizeof(SDL_Surface)));
    m_screen_pos_size = static_cast<SDL_Rect*>(malloc(sizeof(SDL_Surface)));
    *m_init_size = {0, 0, 750, 75};
    *m_screen_pos_size = {15, 20, 250, 25};
    m_background_image = IMG_Load("assets/images/text_input_background.png");
}

TextInput::~TextInput(){
    if(DEBUG) std::cout << __PRETTY_FUNCTION__ << "> freeing TextInput" << std::endl;
    free(m_background_image);
    free(m_init_size);
    free(m_screen_pos_size);
}

// Getters
std::string TextInput::get_text() const{
    if(DEBUG) std::cout << __PRETTY_FUNCTION__ << "> returning text input current text : " << m_current_input << std::endl;
    return m_current_input;
}

bool TextInput::collide(SDL_Event* event) const{
    if(event->button.x > m_screen_pos_size->x && event->button.x < m_screen_pos_size->x + m_screen_pos_size->w)
        if(event->button.y > m_screen_pos_size->y && event->button.y < m_screen_pos_size->y + m_screen_pos_size->h)
            return true;
    return false;
}

// Setters
void TextInput::set_text_size(int w, int h){
    if(DEBUG) std::cout << __PRETTY_FUNCTION__ << "> setting size of text input" << std::endl;
    m_init_size->w = w;
    m_init_size->h = h;
}

// Others
int TextInput::draw(Screen* screen){
    //*m_screen_pos_size = {15, 150, 200, 150};
    return screen->blit(m_tex, m_init_size, *m_screen_pos_size);
}

int TextInput::update(SDL_Event* event, Screen* screen, TTF_Font* font){
    switch(event->type){
        case SDL_TEXTINPUT:
            //Append character
            std::cout << "SDL_TEXTINPUT triggered" << std::endl;
            m_current_input += event->text.text;
            update_image(screen, font);
            return 0;

        case SDL_KEYDOWN:
            if(event->key.keysym.sym == SDLK_RETURN){
                if(DEBUG) std::cout << __PRETTY_FUNCTION__ << "> Stopping TextInput handling" << std::endl;
                SDL_StopTextInput();
                return 1; // Return key has been pressed, the calling function may use this information
            }
            else if(event->key.keysym.sym == SDLK_BACKSPACE){
                //Handle backspace
                if(m_current_input.length() > 0){
                    m_current_input.pop_back();
                    update_image(screen, font);
                }
            }
            else if(event->key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL){
                //Handle copy
                SDL_SetClipboardText(m_current_input.c_str());
            }
            else if(event->key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL){
                //Handle paste
                m_current_input = SDL_GetClipboardText();
                update_image(screen, font);
            }
            return 0; // Text has been modified
        case SDL_MOUSEBUTTONUP:
            if(collide(event)){
                if(DEBUG) std::cout << __PRETTY_FUNCTION__ << "> Starting TextInput handling" << std::endl;
                SDL_StartTextInput();
            }
            else{
                if(DEBUG) std::cout << __PRETTY_FUNCTION__ << "> Stopping TextInput handling" << std::endl;
                SDL_StopTextInput();
            }
            break;
        default:
            ;
    }
    // Nothing happened
    return -1;
}

void TextInput::update_image(Screen* screen, TTF_Font* font){
    if(DEBUG) std::cout << __PRETTY_FUNCTION__ << "> updating TextInput image" << std::endl;

    SDL_Surface* tmp_image = SDL_CreateRGBSurface(0, m_background_image->w, m_background_image->h, 32, 0, 0, 0, 0);
    SDL_BlitSurface(m_background_image, NULL, tmp_image, NULL);
    SDL_BlitSurface(screen->render_text_solid(m_current_input, font, {0, 0, 0, 0}), NULL, tmp_image, NULL);

    m_tex = screen->convert_surface_to_texure(tmp_image);

    SDL_FreeSurface(tmp_image);
}
