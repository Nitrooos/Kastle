#include "World.hpp"

World::World() {
    objects.push_back(Entity{grMananger.getBuffer(ObjectType::Teapot),
                             grMananger.getShader(ObjectType::Teapot), -2, 0, 0});
    objects.push_back(Entity{grMananger.getBuffer(ObjectType::Teapot),
                             grMananger.getShader(ObjectType::Teapot),  2, 0, 0});
    onInit();
}

World::~World() { }

void World::onEvent(Event e) {
    // zakładamy, że obiekty mogą reagować tylko na wciśnięcie klawisza
    if (e.type == Event::KeyPressed) {
        // sprawdzamy czy nie trzeba zaktualizować obiektu kamery
        switch (e.key.code) {
            case Keyboard::Up:
                camera.movEye(0.0f, 0.0f, -0.1f);
                break;
            case Keyboard::Down:
                camera.movEye(0.0f, 0.0f, 0.1f);
                break;
            case Keyboard::Left:
                camera.roll(0.1f);
                break;
            case Keyboard::Right:
                camera.roll(-0.1f);
                break;
            default:
                break;
        }
    }
}

void World::onLoop() {
    float angle = 1.0f;
    for (auto &x : objects) {
        x.roll(angle);
        angle *= -1;
    }
}

void World::onRender() {
    // renderuj każdy obiekt świata po kolei
    for (auto &x : objects)
        x.onRender(camera);
}

void World::onInit() {
    glEnable(GL_DEPTH_TEST);
}
