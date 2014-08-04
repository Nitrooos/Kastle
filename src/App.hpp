#ifndef APP
#define APP

#include <SFML/Window.hpp>
#include <memory>

using namespace std;
using namespace sf;

#include "World.hpp"

class App {
    public:
        App ();
        virtual ~App ();

        void onExecute();

        static constexpr int getWindowWidth()   { return windowWidth;   }
        static constexpr int getWindowHeight()  { return windowHeight;  }

        static Vector2<int>  getWindowCenter()  { return Vector2<int>{windowWidth/2, windowHeight/2}; }
        static constexpr int getWindowCenterX() { return windowWidth/2; }
        static constexpr int getWindowCenterY() { return windowHeight/2;}
    private:
        void initSFML();               // inicjalizacja biblioteki od okienka SFML
        void initGLEW();               // inicjalizacja biblioteki GLEW

        void onInit();                 // inicjalizacja aplikacji
        void onEvent();                // reakcje na zdarzenia
        void onLoop();                 // operacje wykonywane w każdym przebiegu głównej pętli
        void onRender();               // renderowanie sceny

        enum { windowWidth = 800, windowHeight = 600 };
        bool running{true};            // czy aplikacja jeszcze działa?
        Window window;                 // okno aplikacji
        unique_ptr<World> world;       // "świat" złożony z obiektów
};

#endif /* end of include guard: APP */
