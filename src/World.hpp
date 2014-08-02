#ifndef WORLD
#define WORLD

#include <vector>
#include <SFML/Window/Event.hpp>

using namespace std;
using namespace sf;

#include "Entity.hpp"
#include "Camera.hpp"
#include "GraphicsManager.hpp"

class World {
    public:
        World();
        virtual ~World();

        void onEvent(Event e);
        void onLoop();
        void onRender();
    private:
        // akt stworzenia
        void onInit();

        vector<Entity> objects;                 // obiekty należące do świata
        GraphicsManager grMananger;             // manager obiektów rysowanych na scenie
        Camera camera{0.0, 0.0, 7.0};           // kamera, przez którą ogląda świat użytkownik

        static constexpr float 
                         sensitivity = 0.05f;   // jednostka zmiany położenia kamery
        float roll{0.0},                        // o jaki kąt ma się obrócić kamera przy następnej iteracji onLoop?
              go{0.0},                          // o ile przesunąć kamerę w następnej iteracji onLoop (bliżej, dalej)
              height{0.0};                      // o ile przesunąć kamerę w następnej iteracji onLoop (wyżej, niżej)
};

#endif /* end of include guard: WORLD */
