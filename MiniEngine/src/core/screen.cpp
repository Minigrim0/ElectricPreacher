#include "core/screen.hpp"
#include "core/log.hpp"

#include <SDL_render.h>
#include <SDL_image.h>


namespace MiniEngine {
    //Constructors
    Screen::Screen(const WindowProps& props)
        :m_width(props.width),
        m_height(props.height),
        m_tile_size(32),
        m_start_time(0),
        m_time_elapsed(0),
        m_time_since_last_fps_update(0),
        m_fps(0),
        m_showing_fps(false),
        m_window_caption(props.title),
        m_keyConf(std::map<SDL_Keycode, bool>()),
        m_fps_texture(nullptr),
        m_fps_surface(nullptr),
        m_window(nullptr),
        m_Renderer(nullptr),
        m_font_color({ 255, 255, 255, 255 }),
        m_background_color({ 0, 0, 0, 0 }),
        m_fonts(std::map<std::string, TTF_Font*>()),
        m_mouse_pos({ 0, 0, 0, 0 }),
        m_fps_pos({ 0, 0, 0, 0 })
    {}

    Screen::~Screen() {
        //TTF_CloseFont(m_font);
        SDL_FreeSurface(m_fps_surface);
        SDL_DestroyRenderer(m_Renderer);
        SDL_DestroyWindow(m_window);
        TTF_Quit();
        SDL_Quit();
    }

    Screen* Screen::Create(const WindowProps& props) {
        return new Screen(props);
    }

    //Getters
    int Screen::get_width() const { return m_width; }
    int Screen::get_height() const { return m_height; }
    int Screen::get_time_elapsed() const { return static_cast<int>(m_time_elapsed); }

    bool Screen::get_key(SDL_Keycode code) const {
        if (m_keyConf.count(code))
            return m_keyConf.at(code);
        return false;
    }

    std::string Screen::get_caption() const { return m_window_caption; }

    std::map<std::string, TTF_Font*> Screen::get_fonts() const { return m_fonts; }

    TTF_Font* Screen::get_font(std::string font_id) const {
        if (!m_fonts.count(font_id))
            return m_fonts.at("default");
        return m_fonts.at(font_id);
    }

    SDL_Rect Screen::get_mouse_pos() const { return m_mouse_pos; }
    SDL_Window* Screen::get_window() const { return m_window; }
    SDL_Renderer* Screen::get_renderer() const { return m_Renderer; }
    SDL_Color Screen::get_background_color() const { return m_background_color; }


    //Setters
    void Screen::SetWidth(int width) {
        m_width = width;
    }

    void Screen::SetHeight(int height) {
        m_height = height;
    }

    void Screen::SetBackgroundColor(SDL_Color color) {
        m_background_color = color;
    }

    void Screen::SetBackgroundColor(Uint8 r, Uint8 g, Uint8 b) {
        m_background_color.r = r;
        m_background_color.g = g;
        m_background_color.b = b;
    }

    void Screen::SetDefaultFont(std::string font_id) {
        m_fonts["default"] = m_fonts[font_id];
    }

    void Screen::SetCaption(std::string caption) {
        m_window_caption = caption;
        SDL_SetWindowTitle(m_window, m_window_caption.c_str());
    }

    //Others
    int Screen::Init() {
        ME_CORE_TRACE("Initializing SDL");
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_HAPTIC) < 0) {
            ME_CORE_ERROR("SDL could not initialize! SDL_Error: {0}", SDL_GetError());
            return 1;
        }

        ME_CORE_TRACE("Initializing SDL_ttf");
        if (TTF_Init() == -1) {
            ME_CORE_ERROR("TTF could not initialize: {0}", TTF_GetError());
            return 2;
        }

        //Initialize PNG loading
        ME_CORE_TRACE("Initializing SDL_image");
        int imgFlags = IMG_INIT_PNG;
        if (!(IMG_Init(imgFlags) & imgFlags)) {
            ME_CORE_ERROR("Failed to initialize SDL_image : {0}", IMG_GetError());
            return 1;
        }

        return 0;
    }

    int Screen::BuildWindow() {
        if (m_width <= 0 || m_height <= 0) {
            ME_CORE_ERROR("Invalid window size");
            return 1;
        }
        if (m_fonts.find("default") == m_fonts.end()) {
            ME_CORE_ERROR("No default font set");
            return 1;
        }

        ME_CORE_TRACE("Creating window");
        m_window = SDL_CreateWindow(m_window_caption.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_width, m_height, SDL_WINDOW_SHOWN);
        if (m_window == NULL) {
            ME_CORE_ERROR("Failed to create the window : {0}", SDL_GetError());
            return 1;
        }

        ME_CORE_TRACE("Creating renderer");
        m_Renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
        if (m_Renderer == nullptr) {
            ME_CORE_ERROR("Failed to create the renderer : {0}", SDL_GetError());
            return 1;
        }
        SDL_SetRenderDrawColor(m_Renderer, m_background_color.r, m_background_color.g, m_background_color.b, m_background_color.a);

        return 0;
    }

    int Screen::AddFont(std::string path, int size, std::string font_id) {
        if (font_id == "")
            font_id = path + "_" + std::to_string(size);

        if (m_fonts.count(font_id))
            return 0;

        m_fonts[font_id] = TTF_OpenFont(path.c_str(), size);
        if (!m_fonts[font_id]) {
            ME_CORE_ERROR("Failed to load font {0} : {1}", path, TTF_GetError());
            return 3;
        }

        return 0;
    }

    SDL_Surface* Screen::LoadSurface(std::string path) const {
        SDL_Surface* surf = NULL;
        surf = IMG_Load(path.c_str());
        if (surf == NULL)
            ME_CORE_ERROR("Failed to load image {0} : {1}", path, SDL_GetError());

        return surf;
    }

    SDL_Texture* Screen::LoadTexture(std::string path) const {
        SDL_Texture* newTexture = NULL;

        SDL_Surface* loadedSurface = LoadSurface(path.c_str());
        if (loadedSurface != NULL) {
            newTexture = SDL_CreateTextureFromSurface(m_Renderer, loadedSurface);
            if (newTexture == NULL) {
                ME_CORE_ERROR("Failed to create texture from {0} : {1}", path.c_str(), SDL_GetError());
            }
            SDL_FreeSurface(loadedSurface);
        }

        return newTexture;
    }

    SDL_Texture* Screen::Surf2Text(SDL_Surface* surf) const {
        return SDL_CreateTextureFromSurface(m_Renderer, surf);
    }

    SDL_Surface* Screen::render_text_blend(std::string text) {
        return TTF_RenderText_Blended(m_fonts["default"], text.c_str(), m_font_color);
    }

    SDL_Surface* Screen::render_text_blend(std::string text, TTF_Font* font, SDL_Color color) {
        return TTF_RenderText_Blended(font, text.c_str(), color);
    }

    SDL_Surface* Screen::render_text_solid(std::string text) {
        return TTF_RenderText_Solid(m_fonts["default"], text.c_str(), m_font_color);
    }

    SDL_Surface* Screen::render_text_solid(std::string text, TTF_Font* font, SDL_Color color) {
        return TTF_RenderText_Solid(font, text.c_str(), color);
    }

    bool Screen::OnEvent(SDL_Event* event) {
        switch (event->type) {
        case SDL_KEYDOWN:
            m_keyConf[event->key.keysym.sym] = true;
            break;
        case SDL_KEYUP:
            m_keyConf[event->key.keysym.sym] = false;
            if(event->key.keysym.sym == SDLK_F3) {
                FPSDisplayToggle();
                return true;
            }
            break;
        case SDL_MOUSEMOTION:
            m_mouse_pos.x = event->button.x;
            m_mouse_pos.y = event->button.y;
            break;
        case SDL_MOUSEBUTTONDOWN:
            m_keyConf[event->button.button] = true;
            break;
        case SDL_MOUSEBUTTONUP:
            m_keyConf[event->button.button] = false;
            break;
        default:
            break;
        }
        return false;
    }

    void Screen::Update() {
        m_time_elapsed = SDL_GetTicks() - m_start_time;
        m_start_time = SDL_GetTicks();
        m_time_since_last_fps_update += m_time_elapsed;
        if (m_showing_fps) {
            FPSCompute();
            FPSRender();
        }

        SDL_RenderPresent(m_Renderer);
        SDL_RenderClear(m_Renderer);
    }

    void Screen::FPSDisplayToggle() {
        m_showing_fps = !m_showing_fps;
        ME_CORE_TRACE("FPS display toggled to {0}", m_showing_fps ? "true" : "false");
    }

    void Screen::FPSCompute() {
        if (m_time_since_last_fps_update >= 500 && m_time_elapsed != 0) {
            m_fps = static_cast<unsigned int>(1000.0 / static_cast<float>(m_time_elapsed));
            m_time_since_last_fps_update = 0;
            std::string fps_text = std::to_string(m_fps) + " fps";
            SDL_FreeSurface(m_fps_surface);
            m_fps_surface = TTF_RenderText_Blended(m_fonts["default"], fps_text.c_str(), m_font_color);
            if (m_fps_surface == NULL) {
                ME_CORE_ERROR("FPSCompute> Error : {0}", TTF_GetError());
            } else {
                m_fps_pos = { 15, 15, m_fps_surface->w, m_fps_surface->h };
                m_fps_texture = SDL_CreateTextureFromSurface(m_Renderer, m_fps_surface);
            }
        }
    }

    void Screen::FPSRender() {
        if (SDL_RenderCopy(m_Renderer, m_fps_texture, NULL, &m_fps_pos) != 0)
            ME_CORE_ERROR("FPSRender> Error : {0}", SDL_GetError());
    }
}
