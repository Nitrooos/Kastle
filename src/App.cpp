#include "App.hpp"

#include <SFML/Window.hpp>
#include <GL/glew.h>
#include <iostream>

App::App() {
    onInit();
}

App::~App() { }

void App::onInit() {
    initSFML();
    initGLEW();

    world.reset(new World());
}

void App::initSFML() {
    // stwórz okno
    window.create(VideoMode(windowWidth, windowHeight), "OpenGL", Style::Default, ContextSettings(32));
    window.setFramerateLimit(60);
    //window.setVerticalSyncEnabled(true);
}

void App::initGLEW() {
    // inicjalizacja biblioteki GLEW
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        cerr << "Wystąpił błąd: " << glewGetErrorString(err) << "\n";
    }
}

void App::onEvent() {
    // handle events
    Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
            case Event::Closed:
                running = false;
                break;
            case Event::Resized:
                glViewport(0, 0, event.size.width, event.size.height);
                break;
            case Event::KeyPressed:
                if (event.key.code == Keyboard::Escape) {
                    running = false;
                } else
                    world->onEvent(event);
                break;
        }
    }
}



void App::onLoop() {
    world->onLoop();
}

void App::onRender() {
    // wyczyść ekran
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // renderuj scenę
    world->onRender();
    // wyświetl
    window.display();
}

void App::onExecute() {
    // run the main loop
    while (running) {
        onEvent();
        onLoop();
        onRender();
    }
}

int main() {
    try {
        App app;
        app.onExecute();
        return 0;
    } catch (...) {
        cerr << "Niespodziewany wyjątek!\n";            // Kernel Panic
    }
}
