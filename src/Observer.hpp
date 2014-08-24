/*
 * Observator.hpp
 *
 * Copyright 2014 Bartosz Kostaniak <bartas@debian>
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

#ifndef OBSERVER_H
#define OBSERVER_H

#include <vector>

using namespace std;

class Observer {
    public:
        virtual void update(float percent, bool wasOpenGLused = true) = 0;
};

class Observable {
    public:
        virtual void addObserver(Observer *o) {
            observers.push_back(o);
        }

        virtual void notifyObservers(float incPercent, bool wasOpenGLused = true) {
            percent += incPercent;
            for (auto x : observers) {
                x->update(this->percent, wasOpenGLused);
            }
        }
    protected:
        vector<Observer*> observers;
        float percent{0.0f};
};

#endif /* OBSERVATOR_H */
