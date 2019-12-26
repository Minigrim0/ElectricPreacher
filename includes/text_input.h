#include <iostream>

#include <SDL2/SDL.h>


class TextInput{
    public:
        TextInput();
        ~TextInput();

        // Getters
        std::string get_text() const;

        // Setters


        // Others
        void update(SDL_Event event);

    private:
        std::string m_current_input;
        bool m_is_active;
};
