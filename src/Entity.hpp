#ifndef ENTITY
#define ENTITY

#include "glm/glm.hpp"
#include <string>

using namespace std;
using namespace glm;

#include "LightsMaterials.hpp"
#include "Camera.hpp"
#include "ShaderProgram.hpp"
#include "ObjectBuffers.hpp"

class Entity {
    public:
        Entity(ObjectBuffers *ob, ShaderProgram *sp, double x, double y, double z, GLuint tex0, GLuint tex1 = 0);
        virtual ~Entity();

        void onLoop();
        void onRender(const Camera &c, const Light &l, const Light &l1, const Material &m);

        void move(double movX, double movY, double movZ);
        void setPosition(double x, double y, double z);
        void roll(double rotAngle);
        void setAngle(double angle);

        float getX() const { return x; }
        float getY() const { return y; }
        float getZ() const { return z; }
    private:
        void updateMatrixM();

        ShaderProgram *shaderProgram;           // pointer do programu cieniującego
        ObjectBuffers *objectBuffers;           // pointer do buforów vbo
        GLuint tex0{0}, tex1{0};                // tekstury obiektu (można użyć max dwóch)

        float x, y, z;                          // wsp obiektu na scenie
        float angle{0.0};                       // kąt obrotu (początkowo 0.0)

        mat4 matrixM;                           // macierz modelu
};

#endif /* end of include guard: Entity */
