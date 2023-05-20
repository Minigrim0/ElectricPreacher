#include <SDL.h>
#include <SDL_image.h>

#include "UI/widgets/text_input.hpp"

#include "core/application.hpp"

namespace MiniEngine {
    namespace UI {
        namespace Widgets {
            TextInput::TextInput()
                : m_tex(nullptr),
                  m_cursor(nullptr),
                  m_background_image(nullptr),
                  m_rect({0, 0, 0, 0}),
                  m_font(nullptr),
                  m_current_input(""),
                  m_cursor_pos(0),
                  m_selection_len(0),
                  m_is_active(false)
            {
                m_background_image = IMG_Load("assets/images/text_input_background.png");
                SDL_StopTextInput();
            }

            TextInput::~TextInput()
            {
                free(m_background_image);
                SDL_FreeSurface(m_background_image);
                SDL_DestroyTexture(m_tex);
            }

            // Getters
            std::string TextInput::get_text() const
            {
                return m_current_input;
            }

            bool TextInput::collide(SDL_Event *event) const
            {
                if (event->button.x > m_rect.x && event->button.x < m_rect.x + m_rect.w)
                    if (event->button.y > m_rect.y && event->button.y < m_rect.y + m_rect.h)
                        return true;
                return false;
            }

            bool TextInput::collide(int x, int y) const
            {
                if (x > m_rect.x && x < m_rect.x + m_rect.w)
                    if (y > m_rect.y && y < m_rect.y + m_rect.h)
                        return true;
                return false;
            }

            TTF_Font *TextInput::get_font() const
            {
                return m_font;
            }

            bool TextInput::is_empty() const
            {
                return m_current_input.length() == 0;
            }

            // Setters
            void TextInput::set_position(int x, int y)
            {
                m_rect.x = x;
                m_rect.y = y;
            }

            void TextInput::set_text_size(int w, int h)
            {
                m_rect.w = w;
                m_rect.h = h;
            }

            void TextInput::set_font(std::string font_path, int size)
            {
                m_font = TTF_OpenFont(font_path.c_str(), size);
                if (m_font == nullptr)
                {
                    std::cout << "Error while loading font for text input : " << TTF_GetError() << std::endl;
                }
            }

            void TextInput::set_font(TTF_Font *font)
            {
                m_font = font;
            }

            // Others
            void TextInput::OnRender(Screen *sc)
            {
                SDL_RenderCopy(sc->get_renderer(), m_tex, NULL, &m_rect);
            }

            bool TextInput::OnEvent(SDL_Event *event)
            {
                switch (event->type)
                {
                case SDL_TEXTINPUT:
                    // Append character
                    m_current_input += event->text.text;
                    update_image();
                    return true;
                case SDL_KEYDOWN:
                    if (SDL_IsTextInputActive())
                    {
                        if (event->key.keysym.sym == SDLK_RETURN)
                        {
                            SDL_StopTextInput();
                        }
                        else if (event->key.keysym.sym == SDLK_BACKSPACE)
                        {
                            // Handle backspace
                            if (m_current_input.length() > 0)
                            {
                                m_current_input.pop_back();
                                update_image();
                            }
                        }
                        else if (event->key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL)
                        {
                            // Handle copy
                            SDL_SetClipboardText(m_current_input.c_str());
                        }
                        else if (event->key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL)
                        {
                            // Handle paste
                            m_current_input = SDL_GetClipboardText();
                            update_image();
                        }
                        else
                        {
                            return false;
                        }

                        return true;
                    }
                    break;
                case SDL_MOUSEBUTTONUP:
                    if (collide(event) && !SDL_IsTextInputActive())
                    {
                        SDL_StartTextInput();
                    }
                    else if (!collide(event) && SDL_IsTextInputActive())
                    {
                        SDL_StopTextInput();
                    }
                    else
                    {
                        return false;
                    }
                    m_is_active = SDL_IsTextInputActive();
                    return true;
                    break;
                default:;
                }
                // Nothing happened
                return false;
            }

            void TextInput::OnUpdate(int time_elaped) {}

            void TextInput::update_image()
            {
                Screen *screen = Application::GetInstance()->get_screen();

                SDL_Surface *tmp_image = SDL_CreateRGBSurface(0, m_background_image->w, m_background_image->h, 32, 0, 0, 0, 0);
                SDL_BlitSurface(m_background_image, NULL, tmp_image, NULL);

                SDL_BlitSurface(screen->render_text_blend(m_current_input, m_font, {0, 0, 0, 0}), NULL, tmp_image, NULL);
                m_tex = screen->convert_surface_to_texure(tmp_image);

                SDL_FreeSurface(tmp_image);
            }

            void TextInput::flush()
            {
                m_current_input = "";
                update_image();
            }
        }
    }
}