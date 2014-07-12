#ifndef WORLD
#define WORLD

#include <GL/glew.h>
#include <vector>
#include <SFML/Window/Event.hpp>

using namespace std;
using namespace sf;

//#include "Object.hpp"
#include "Camera.hpp"
#include "ShaderProgram.hpp"
#include "ObjectBuffers.hpp"
//#include "GraphicsManager.hpp"

#include <memory>

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

        //vector<Object> objects;             // obiekty należące do świata
        //GraphicsManager grMananger;         // manager obiektów rysowanych na scenie
        Camera camera;                      // kamera, przez którą ogląda świat użytkownik

        //Macierze
        mat4    matP,                           //rzutowania
                matV,                           //widoku
                matM;                           //modelu

        //Uchwyty na shadery
        unique_ptr<ShaderProgram> shaderProgram;
        unique_ptr<ObjectBuffers> objectBuffers;

        // Liczba wierzchołków modelu
        int vertexCount;
};

#endif /* end of include guard: WORLD */
