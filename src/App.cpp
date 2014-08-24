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

    grMananger.reset(new GraphicsManager());
    loadingScreen.reset(new LoadingScreen(window, grMananger.get()));
    world.reset(new World(grMananger.get()));
}

void App::initSFML() {
    // stwórz okno
    window.create(VideoMode(windowWidth, windowHeight), "OpenGL", Style::Default, ContextSettings(32));
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);
    window.setMouseCursorVisible(false);

    Mouse::setPosition(getWindowCenter(), window);
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
            case Event::KeyReleased:
                if (event.key.code == Keyboard::Escape) {
                    running = false;
                } else
                    world->onKeyboardEvent(event);
                break;
            case Event::MouseLeft:
            case Event::MouseMoved:
                if (Mouse::getPosition(window) != getWindowCenter()) {
                    world->onMouseEvent(Mouse::getPosition(window));
                    Mouse::setPosition(getWindowCenter(), window);
                }
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
