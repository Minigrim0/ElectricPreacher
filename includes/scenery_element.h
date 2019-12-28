#ifndef scenery_element_h
    #define scenery_element_h

/**
    name : scenery_element.h
    purpose : Defines an element of the scenery (i.e. : a sign, a lever,...)
*/

#include <SDL2/SDL.h>
#include "map_element.h"

class SceneryElement : public MapElement{
    public:
        //Constructors
        SceneryElement();
        ~SceneryElement();

        //Getters
        int get_type() const;

        //Setters
        void set_type(int);

        //Others

    private:
        int m_type;

};

#endif
