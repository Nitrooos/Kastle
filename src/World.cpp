#include "World.hpp"

World::World() {
    Entity obj(grMananger.getBuffer(ObjectType::Teapot),
               grMananger.getShader(ObjectType::Teapot), 0, 0, 0);
    objects.push_back(obj);

    onInit();
}

World::~World() { }

void World::onEvent(Event e) {
    // zakładamy, że obiekty mogą reagować tylko na wciśnięcie klawisza
    if (e.type == Event::KeyPressed) {
        // sprawdzamy czy nie trzeba zaktualizować obiektu kamery
        switch (e.key.code) {
           default:
                break;
        }
    }
}

void World::onLoop() {
    objects.front().roll(1.0f);
}

void World::onRender() {
    // renderuj każdy obiekt świata po kolei
    for (auto &x : objects)
        x.onRender(camera);
}

void World::onInit() {
    glEnable(GL_DEPTH_TEST);
}
