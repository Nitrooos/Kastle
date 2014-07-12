#ifndef CAMERA
#define CAMERA

#include "glm/glm.hpp"

using namespace glm;

class Camera {
    public:
        Camera();
        virtual ~Camera();

        void movEyeX(double mov);       // przesuń oko kamery wzdłuż osi X
        void movEyeY(double mov);       // przesuń oko kamery wzdłuż osi Y
        void movEyeZ(double mov);       // przesuń oko kamery wzdłuż osi Z

        double getX() const;            // pobierz odpowiednią współrzędną
        double getY() const;
        double getZ() const;

        const mat4& getMatrixV() const;
        const mat4& getMatrixP() const;
    private:
        // współrzędne oka kamery oraz punkt widzenia kamery (środek sceny)
        double x{0.0}, y{0.0}, z{0.0},
               centerX{0.0}, centerY{5.0}, centerZ{0.0};
        mat4 matrixV, matrixP;
};

#endif /* end of include guard: CAMERA */
