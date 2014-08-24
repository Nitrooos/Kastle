/*
 * LoadingScreen.hpp
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

#ifndef LOADINGSCREEN_H
#define LOADINGSCREEN_H

#include <SFML/Graphics.hpp>

#include "GraphicsManager.hpp"
#include "Observer.hpp"

using namespace sf;

class LoadingScreen : public Observer {
    public:
        LoadingScreen(RenderWindow &window, GraphicsManager *gm);

        void update(float percent, bool wasOpenGLused = true);
    private:
        void onInit();

        GraphicsManager *grMananger;            // manager zasobów (informuje o stanie ładowania)
        RenderWindow &window;                   // okienko, na którym rysowany jestr pasek postępu ładowania

        Texture kastle;                         // tło od Dako
        Sprite background;                      // sprite do wyświetlenia jako tło
        RectangleShape progressBar;             // pasek postępu
        Font font;                              // font wyświetlanego tekstu
        Text text;                              // wyświetlany tekst
};

#endif /* LOADINGSCREEN_H */
