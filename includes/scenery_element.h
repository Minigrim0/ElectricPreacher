#ifndef scenery_element_h
    #define scenery_element_h

/**
    name : scenery_element.h
    purpose : contains the prototypes for SceneryElement class
*/

#include <SDL2/SDL.h>
#include "map_element.h"

/**
    Class : SceneryElement
    purpose : Defines an element of the scenery (i.e. : a sign, a lever,...)
*/
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
