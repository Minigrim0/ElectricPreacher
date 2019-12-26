#include <vector>

#include "screen.h"
#include "button.h"
#include "text_input.h"

class Console{
    public:
        // Constructors
        Console();
        ~Console();

        // Getters


        // Setters


        // Others
        int draw(Screen screen);

    private:
        std::vector<Button> m_history;
        TextInput m_input;
};
