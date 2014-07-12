#ifndef ENTITY
#define ENTITY

#include "glm/glm.hpp"
#include <string>

using namespace std;
using namespace glm;

#include "Camera.hpp"
#include "ShaderProgram.hpp"
#include "ObjectBuffers.hpp"

class Entity {
    public:
        Entity(ObjectBuffers *ob, ShaderProgram *sp, double x, double y, double z);
        virtual ~Entity();

        void onLoop();
        void onRender(const Camera &c);

        void move(double movX, double movY, double movZ);
        void setPosition(double x, double y, double z);
        void roll(double rotAngle);
        void setAngle(double angle);
    private:
        void updateMatrixM();

        ShaderProgram *shaderProgram;           // pointer do programu cieniującego
        ObjectBuffers *objectBuffers;           // pointer do buforów vbo

        float x, y, z;                          // wsp obiektu na scenie
        float angle{0.0};                       // kąt obrotu (początkowo 0.0)

        mat4 matrixM;                           // macierz modelu
};

#endif /* end of include guard: Entity */
