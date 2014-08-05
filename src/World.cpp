#include "World.hpp"
#include "App.hpp"

World::World() {
    /*objects.push_back(Entity{grMananger.getBuffer(ObjectType::Teapot),
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
                     );*/
    objects.push_back(Entity{grMananger.getBuffer(ObjectType::Hall),
                             grMananger.getShader(ObjectType::Hall),
                             0, 0, 5,
                             grMananger.getTexture(TextureType::Purple)}
                     );
    onInit();
}

World::~World() { }

void World::onKeyboardEvent(Event e) {
    // zakładamy, że obiekty mogą reagować tylko na wciśnięcie klawisza
    switch (e.type) {
        case Event::KeyPressed:
            switch (e.key.code) {
                case Keyboard::W: go     = -sensitivity; break;
                case Keyboard::S: go     =  sensitivity; break;
                case Keyboard::A: side   = -sensitivity; break;
                case Keyboard::D: side   =  sensitivity; break;
                case Keyboard::K: height =  sensitivity; break;
                case Keyboard::M: height = -sensitivity; break;
            }
            break;
        case Event::KeyReleased:
            switch (e.key.code) {
                case Keyboard::W: case Keyboard::S: go     = 0.0f; break;
                case Keyboard::A: case Keyboard::D: side   = 0.0f; break;
                case Keyboard::K: case Keyboard::M: height = 0.0f; break;
            }
            break;
    }
}

void World::onMouseEvent(const Vector2<int> &pos) {
    int diffX = App::getWindowCenterX() - pos.x,
        diffY = App::getWindowCenterY() - pos.y;

    camera.roll(diffX/400.0f, diffY/400.0f);
}

void World::onLoop() {
    /*float angle = 1.0f;
    for (auto &x : objects) {
        x.roll(angle);
        angle *= -1;
    }*/

    if (this->go != 0.0f || this->height != 0.0f)
        camera.movEye(-camera.getZShift(this->go), this->height, camera.getXShift(this->go));
    if (this->side != 0.0f)
        camera.movEye(camera.getXShift(this->side), 0, camera.getZShift(this->side));

    camera.writeCoordinates();
}

void World::onRender() {
    // renderuj każdy obiekt świata po kolei
    for (auto &x : objects)
        x.onRender(camera);
}

void World::onInit() {
    glEnable(GL_DEPTH_TEST);
}
