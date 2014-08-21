#include "Camera.hpp"
#include "App.hpp"

#include <iostream>
#include <iomanip>
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

    centerX += movX;
    centerY += movY;
    centerZ += movZ;

    updateMatrixV();

    //cout << "x: " << x << "\ty: " << y << "\tz: " << z << "\n";
}

void Camera::roll(float cenX, float cenY, float cenZ) {
    centerX += cenX;
    centerY += cenY;
    centerZ += cenZ;
    updateMatrixV();
}

void Camera::roll(float changeLeftRight, float changeUpDown) {
    //cout << "centerX: " << centerX << "\tcenterY: " << centerY << "\tcenterZ: " << centerZ << "\n";

    paramTLeftRight += changeLeftRight;
    paramTUpDown += changeUpDown;

    centerX = x + 20*cos(paramTLeftRight)*cos(paramTUpDown);
    centerY = y + 20*sin(paramTUpDown);
    centerZ = z - 20*sin(paramTLeftRight)*cos(paramTUpDown);

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

float Camera::getXShift(float velocity) const {
    return velocity*sin(paramTLeftRight);
}

float Camera::getZShift(float velocity) const {
    return velocity*cos(paramTLeftRight);
}

const mat4& Camera::getMatrixV() const {
    return matrixV;
}

const mat4& Camera::getMatrixP() const {
    return matrixP;
}

void Camera::writeCoordinates() const {
    cout << fixed << setw(15) << "\rx: " << x << "  y: " << y << "  z: " << z << flush;
}

void Camera::updateMatrixV() {
    matrixV = lookAt(vec3(x, y, z), vec3(centerX, centerY, centerZ), vec3(0.0f,1.0f,0.0f));
}

