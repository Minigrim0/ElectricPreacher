#include "../includes/text_input.h"
#include "../includes/constants.h"

TextInput::TextInput()
:m_tex(nullptr),
m_init_size(),
m_screen_pos_size(nullptr),
m_current_input("aeeae"),
m_is_active(false)
{
    if(DEBUG) std::cout << __PRETTY_FUNCTION__ << "> Creating new TextInput" << std::endl;
    m_init_size = static_cast<SDL_Rect*>(malloc(sizeof(SDL_Surface)));
    m_screen_pos_size = static_cast<SDL_Rect*>(malloc(sizeof(SDL_Surface)));
    *m_init_size = {0, 0, 200, 150};
    *m_screen_pos_size = {20, 20, 200, 150};
}

TextInput::~TextInput(){
    if(DEBUG) std::cout << __PRETTY_FUNCTION__ << "> freeing TextInput" << std::endl;
    free(m_init_size);
    free(m_screen_pos_size);
}

// Getters
std::string TextInput::get_text() const{
    if(DEBUG) std::cout << __PRETTY_FUNCTION__ << "> returning text input current text : " << m_current_input << std::endl;
    return m_current_input;
}

// Setters
void TextInput::set_text_size(int w, int h){
    if(DEBUG) std::cout << __PRETTY_FUNCTION__ << "> setting size of text input" << std::endl;
    m_init_size->w = w;
    m_init_size->h = h;
}

// Others
int TextInput::draw(Screen* screen){
    *m_screen_pos_size = {0, 0, 200, 150};
    return screen->blit(m_tex, m_init_size, *m_screen_pos_size);
}


int TextInput::update(SDL_Event event){
    if(event.type == SDL_KEYDOWN){
        switch(event.key.keysym.sym){
            case SDLK_RETURN:
                return 1; // Return kay has been pressed, the calling function may use this information
            case SDLK_BACKSPACE:
                backspace();
                break;
            default:
                break;
        }
        return 0; // Text has been modified
    }
    return -1; // Nothing happened
}

void TextInput::backspace(){
    m_current_input = m_current_input.substr(0, m_current_input.size()-1);
}

void TextInput::update_image(Screen* screen, TTF_Font* font){
    if(DEBUG) std::cout << __PRETTY_FUNCTION__ << "> updating TextInput image" << std::endl;

    SDL_Surface* tmp_image = SDL_CreateRGBSurface(0, m_init_size->w, m_init_size->h, 32, 0, 0, 0, 0);
    SDL_BlitSurface(screen->render_text_solid(m_current_input, font), NULL, tmp_image, NULL);

    m_tex = screen->convert_surface_to_texure(tmp_image);

    SDL_FreeSurface(tmp_image);
}
