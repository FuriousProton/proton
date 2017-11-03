#include <GLFW/glfw3.h>

#include "utility.h"
#include "engine/DisplaySettings.h"
#include "engine/Proton.h"
#include "engine/entity/Entity.h"
#include "engine/component/Renderer.h"


int main()
{
    using namespace proton;

    DisplaySettings dSettings;
    dSettings.title="Game";
    Proton p{};
    p.createDisplay(dSettings);
    glBegin(GL_TRIANGLES);
    glColor3b(10,10,10);

    auto *e = new Entity();
    auto *r = new Renderer("simple.shader");

    e->addComponent(r);

    glVertex2d(-0.9,-0.9);
    glVertex2d(0.9,-0.9);
    glVertex2d(0,0.9);

    glEnd();
    p.startLoop();


    return 0;
}
