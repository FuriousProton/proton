#include <GLFW/glfw3.h>

#include "utility.h"
#include "engine/DisplaySettings.h"
#include "engine/Proton.h"

int main()
{

    DisplaySettings dSettings;
    dSettings.title="Game";
    Proton p{};
    p.createDisplay(dSettings);
    glBegin(GL_TRIANGLES);
    glColor3b(10,10,10);

    glVertex2d(-0.9,-0.9);
    glVertex2d(0.9,-0.9);
    glVertex2d(0,0.9);

    glEnd();
    p.startLoop();


    return 0;
}