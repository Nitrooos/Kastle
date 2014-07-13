#include "Camera.hpp"
#include "App.hpp"

#include <iostream>
#include "glm/gtc/matrix_transform.hpp"

Camera::Camera(float x, float y, float z) : x(x), y(y), z(z) {
    updateMatrixV();
    matrixP = perspective(45.0f, (float)App::getWindowWidth()/(float)App::getWindowHeight(), 1.0f, 100.0f);
}

Camera::~Camera() { }

void Camera::movEye(float movX, float movY, float movZ) {
    x += movX;
    y += movY;
    z += movZ;
    updateMatrixV();
}

void Camera::roll(float cenX, float cenY, float cenZ) {
    centerX += cenX;
    centerY += cenY;
    centerZ += cenZ;
    updateMatrixV();
}

void Camera::roll(float changeT) {
    //cout << "centerX: " << centerX << "\tcenterY: " << centerY << "\tcenterZ: " << centerZ << "\n";

    paramT += changeT;
    centerX = 7*cos(paramT);
    centerZ = -7*sin(paramT);
    updateMatrixV();

    //cout << "centerX: " << centerX << "\tcenterY: " << centerY << "\tcenterZ: " << centerZ << "\n";
}

float Camera::getX() const {
    return x;
}

float Camera::getY() const {
    return y;
}

float Camera::getZ() const {
    return z;
}

const mat4& Camera::getMatrixV() const {
    return matrixV;
}

const mat4& Camera::getMatrixP() const {
    return matrixP;
}

void Camera::updateMatrixV() {
    matrixV = lookAt(vec3(x, y, z), vec3(centerX, centerY, centerZ), vec3(0.0f,1.0f,0.0f));
}
