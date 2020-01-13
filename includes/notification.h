#ifndef notif_h
    #define notif_h

#include <iostream>

#include "widgets.h"

class Notification: public Widget{
    public:
        // Constructors
        Notification();
        ~Notification();

        // Others
        int draw(Screen*) override;
        int update(SDL_Event*, Screen*) override;

    private:
        std::string m_content;

};

#endif
