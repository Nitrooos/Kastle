/*
 * Animation.hpp
 *
 * Copyright 2014 Bartosz Kostaniak <bartosz@inspiron>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301  USA.
 *
 */

#ifndef ANIMATION_H
#define ANIMATION_H

#include "Entity.hpp"

class Animation {
    public:
        enum Status { Running, Stop };

        Animation(Entity &object);

        void setParams(float rollAngle, float stopAngle);
        void animate();
        Status getStatus();
    private:
        Entity &object;
        float rollAngle{0.0f},
              culmutativeAngle{0.0f},
              stopAngle{0.0f};
        Status status{Status::Running};
};

#endif /* ANIMATION_H */
