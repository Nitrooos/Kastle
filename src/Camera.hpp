#ifndef CAMERA
#define CAMERA

#include "glm/glm.hpp"
#include <cmath>

using namespace glm;
using namespace std;

class Camera {
    public:
        Camera(float x, float y, float z);
        virtual ~Camera();

        // przesuń oko kamery wzdłuż osi
        void movEye(float movX, float movY, float movZ);
        void roll(float cenX, float cenY, float cenZ);
        void roll(float changeT);

        // pobierz odpowiednią współrzędną
        float getX() const;
        float getY() const;
        float getZ() const;

        // Zwraca przesunięcie x/z o jakie należy przenieść kamerę przy poruszaniu z daną prędkością
        float getXShift(float velocity) const;
        float getZShift(float velocity) const; 

        const mat4& getMatrixV() const;
        const mat4& getMatrixP() const;
    private:
        void updateMatrixV();
        void updateAlfaAngle();

        // współrzędne oka kamery oraz punkt widzenia kamery (środek sceny)
        float x{0.0}, y{0.0}, z{0.0},
               centerX{0.0}, centerY{0.0}, centerZ{0.0},
               paramT{M_PI_2};
        float alfa{0.0};
        mat4 matrixV, matrixP;
};

#endif /* end of include guard: CAMERA */
