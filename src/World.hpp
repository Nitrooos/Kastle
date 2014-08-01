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

        vector<Entity> objects;             // obiekty należące do świata
        GraphicsManager grMananger;         // manager obiektów rysowanych na scenie
        Camera camera{0.0, 0.0, 7.0};       // kamera, przez którą ogląda świat użytkownik
};

#endif /* end of include guard: WORLD */
