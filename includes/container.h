#ifndef container_h
    #define container_h

#include "widgets.h"
#include <SDL2/SDL_rect.h>

class Container : public Widget{
    public:
        Container();
        virtual ~Container();

        Container& operator=(const Container&);

        //Others
        int draw(Screen*  screen) override;
        int update(SDL_Event* event, Screen* screen) override;

    private:
        SDL_Rect m_rect;
        std::vector<Widget*> m_widgets;
};

#endif
