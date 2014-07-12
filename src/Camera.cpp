#include "Camera.hpp"
#include "App.hpp"

#include "glm/gtc/matrix_transform.hpp"

Camera::Camera() {
    matrixV = lookAt(vec3(0.0f,0.0f,7.0f), vec3(0.0f,0.0f,0.0f), vec3(0.0f,1.0f,0.0f));
    matrixP = perspective(45.0f, (float)App::getWindowWidth()/(float)App::getWindowHeight(), 1.0f, 100.0f);
}

Camera::~Camera() { }

void Camera::movEyeX(double mov) {
    x += mov;
}

void Camera::movEyeY(double mov) {
    y += mov;
}

void Camera::movEyeZ(double mov) {
    z += mov;
}

double Camera::getX() const {
    return x;
}

double Camera::getY() const {
    return y;
}

double Camera::getZ() const {
    return z;
}

const mat4& Camera::getMatrixV() const {
    return matrixV;
}

const mat4& Camera::getMatrixP() const {
    return matrixP;
}
