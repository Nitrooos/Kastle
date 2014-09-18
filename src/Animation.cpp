#include "Animation.hpp"

Animation::Animation(Entity &object) : object(object) { }

void Animation::setParams(float rollAngle, float stopAngle) {
    this->rollAngle = rollAngle;
    this->stopAngle = stopAngle;
}

Status Animation::animate() {
    if (culmutativeAngle < stopAngle) {
        object.roll(rollAngle);
        return Status::Running;
    } else
        return Status::Stop;
}
