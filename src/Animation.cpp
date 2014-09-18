#include "Animation.hpp"

Animation::Animation(Entity &object) : object(object) { }

void Animation::setParams(float rollAngle, float stopAngle) {
    this->rollAngle = rollAngle;
    this->stopAngle = stopAngle;
}

void Animation::animate() {
    if (abs(culmutativeAngle) < stopAngle) {
        object.roll(rollAngle);
        culmutativeAngle += rollAngle;
    } else
        status = Status::Stop;
}

Animation::Status Animation::getStatus() const {
    return status;
}
