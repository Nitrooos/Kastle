#include "Animation.hpp"

Animation::Animation(Entity &object) : object(object) { }

void Animation::setParams(float rollAngle, float stopAngle) {
    this->rollAngle = rollAngle;
    this->stopAngle = stopAngle;
}

void Animation::animate() {
    if (culmutativeAngle < stopAngle)
        object.roll(rollAngle);
    else
        status = Status::Stop;
}

Status Animation::getStatus() {
    return status;
}
