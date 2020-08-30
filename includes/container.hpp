#ifndef container_h
    #define container_h

#include <SDL2/SDL_rect.h>

#include "widgets.hpp"

class Container : public Widget{
    public:
        Container();
        virtual ~Container();

        Container& operator=(const Container&);

        //Others
        int draw(Screen*  screen) override;
        int update(SDL_Event* event, Screen* screen) override;

    private:
        int type;
        SDL_Rect m_rect;
        std::vector<Widget*> m_widgets;
};

#endif
