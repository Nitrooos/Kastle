#ifndef WORLD
#define WORLD

#include <vector>
#include <list>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Image.hpp>

using namespace std;
using namespace sf;

#include "glm/glm.hpp"
#include "Entity.hpp"
#include "Animation.hpp"
#include "Camera.hpp"
#include "LightsMaterials.hpp"
#include "GraphicsManager.hpp"

class World {
    public:
        World(GraphicsManager *gm);
        virtual ~World();

        void onKeyboardEvent(Event e);
        void onMouseEvent(const Vector2<int> &pos);
        void onLoop();
        void onRender();
    private:
        // akt stworzenia
        void onInit();
        bool isCollision(float xShift, float zShift) const;       // czy na nowych wsp camery wystąpi kolizja z obiektem?
        void checkAction();
        void teleport();
        void openDoors();

        GraphicsManager *grMananger;            // manager obiektów rysowanych na scenie
        vector<Entity> objects;                 // obiekty należące do świata
        list<Animation> animations;             // animacje obiektów na scenie
        Camera camera{-10.0, 3.0, 80.0};        // kamera, przez którą ogląda świat użytkownik
        bool cameraOnFirstFloor{false};         // czy gracz jest na piętrze?

        Image collisionMap,                     // czarno-biały obrazek wskazujący miejsca kolizji w zamku z góry
              firstFloorCollisionMap;           // mapa kolizji dla piętra (aby gracz nie przechodził przez barierki)

        Light lights[2];                        // swiatla
        Material materials[2];                  // materialy

        static constexpr float
                         sensitivity = 0.2f;    // jednostka zmiany położenia kamery
        float go{0.0},                          // o ile przesunąć kamerę w następnej iteracji onLoop (bliżej, dalej)
              side{0.0},                        // o ile przesunąć kamerę w następnej iteracji onLoop (w lewo, w prawo)
              height{0.0},                      // o ile przesunąć kamerę w następnej iteracji onLoop (wyżej, niżej)
              headParam{0.0};                   // parametr x funkcji sin x po wykresie której porusza się kamera

        bool rotateObjects{false};              // czy włączyć obracanie obiektów?
};

#endif /* end of include guard: WORLD */
