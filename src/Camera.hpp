#ifndef CAMERA
#define CAMERA

#include "glm/glm.hpp"

using namespace glm;

class Camera {
    public:
        Camera(float x, float y, float z);
        virtual ~Camera();

        // przesuń oko kamery wzdłuż osi
        void movEye(float movX, float movY, float movZ);
        void roll(float cenX, float cenY, float cenZ);

        // pobierz odpowiednią współrzędną
        float getX() const;
        float getY() const;
        float getZ() const;

        const mat4& getMatrixV() const;
        const mat4& getMatrixP() const;
    private:
        void updateMatrixV();

        // współrzędne oka kamery oraz punkt widzenia kamery (środek sceny)
        float x{0.0}, y{0.0}, z{0.0},
               centerX{0.0}, centerY{0.0}, centerZ{0.0};
        mat4 matrixV, matrixP;
};

#endif /* end of include guard: CAMERA */
