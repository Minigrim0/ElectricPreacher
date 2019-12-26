#include <iostream>
#include <vector>

template <typename T>
class Widget{
    public:
        //Constructors
        Widget():
        m_children(std::vector<T*>())
        {}

        Widget(Widget<T>&):
        m_children(std::vector<T*>())
        {}

        ~Widget(){}

        //Getters
        T* get_children(){
            return m_children;
        }

        T* get_child(int childNb){
            return m_children[childNb];
        }

        //Setters

        //Others

    private:
        std::vector<T*> m_children;
};
