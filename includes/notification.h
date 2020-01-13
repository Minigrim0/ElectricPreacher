#ifndef notif_h
    #define notif_h

#include <iostream>

#include "widgets.h"

class Notification: public Widget{
    public:
        // Constructors
        Notification();
        Notification(const Notification&);
        ~Notification();

        // Operator
        Notification& operator=(const Notification&);

        // Setters
        void set_position(int, int);
        void set_text(std::string);
        void set_icon(SDL_Texture*);

        // Others
        int draw(Screen*) override;
        int update(SDL_Event*, Screen*) override;

    private:
        std::string m_content;

        SDL_Texture* m_background;
        SDL_Texture* m_text_texture;
        SDL_Texture* m_icon;

};

#endif
