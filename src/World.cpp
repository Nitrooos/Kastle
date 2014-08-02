#include "World.hpp"

World::World() {
    objects.push_back(Entity{grMananger.getBuffer(ObjectType::Teapot),
                             grMananger.getShader(ObjectType::Teapot),
                             -2, 0, 0,
                             grMananger.getTexture(TextureType::Metal),
                             grMananger.getTexture(TextureType::Sky)}
                     );
    objects.push_back(Entity{grMananger.getBuffer(ObjectType::Teapot),
                             grMananger.getShader(ObjectType::Teapot),
                             2, 0, 0,
                             grMananger.getTexture(TextureType::Metal),
                             grMananger.getTexture(TextureType::Stone)}
                     );
    onInit();
}

World::~World() { }

void World::onEvent(Event e) {
    // zakładamy, że obiekty mogą reagować tylko na wciśnięcie klawisza
    switch (e.type) {
        case Event::KeyPressed:
            switch (e.key.code) {
                case Keyboard::Up:      go     = -sensitivity; break;
                case Keyboard::Down:    go     =  sensitivity; break;
                case Keyboard::Left:    roll   =  sensitivity; break;
                case Keyboard::Right:   roll   = -sensitivity; break;
                case Keyboard::K:       height =  sensitivity; break;
                case Keyboard::M:       height = -sensitivity; break;
            }
            break;
        case Event::KeyReleased:
            switch (e.key.code) {
                case Keyboard::Up: case Keyboard::Down:      go     = 0.0f; break;
                case Keyboard::Left: case Keyboard::Right:   roll   = 0.0f; break;
                case Keyboard::K: case Keyboard::M:          height = 0.0f; break;
            }
            break;
    }
}

void World::onLoop() {
    float angle = 1.0f;
    for (auto &x : objects) {
        x.roll(angle);
        angle *= -1;
    }

    if (this->go != 0.0f || this->height != 0.0f)
        camera.movEye(camera.getXShift(this->go), this->height, camera.getZShift(this->go));
    if (this->roll != 0.0f)
        camera.roll(this->roll);
}

void World::onRender() {
    // renderuj każdy obiekt świata po kolei
    for (auto &x : objects)
        x.onRender(camera);
}

void World::onInit() {
    glEnable(GL_DEPTH_TEST);
}
