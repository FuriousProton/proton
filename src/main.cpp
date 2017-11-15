#include <GLFW/glfw3.h>

#include "utility.h"
#include "engine/DisplaySettings.h"
#include "engine/Proton.h"
#include "engine/entity/Entity.h"
#include "engine/component/Renderer.h"
#include "engine/Scene.h"
#include "interface/graphics/IndexBuffer.h"
#include "interface/graphics/VertexArray.h"
#include "interface/graphics/Buffer.h"
#include "engine/entity/Camera.h"

int main()
{
    using namespace proton;

    DisplaySettings dSettings;
    dSettings.title="Game";
    Proton p{};
    auto *scene = new Scene();
    p.createDisplay(dSettings);
    auto *c = new Camera(800,600,70,.01f,1000);
    auto *e = new Entity();
    auto *r = new Renderer("simple.shader");
    scene->addEntity(c);
#define IBO_LEN 3
    unsigned int indexes[IBO_LEN]={
            0,2,1
    };
    IndexBuffer ibo(indexes,IBO_LEN);
    VertexArray vao;
#define VBO_LEN 9
    float vert[VBO_LEN]={
            -0.5f,0,0,
            0.5f,0,0,
            0,0.5f,0
    };
    Buffer verticles(vert,VBO_LEN,3);
    vao.addBuffer(&verticles,0);
    r->setModel(&ibo,&vao);
    e->addComponent(r);
    scene->addEntity(e);
    scene->activate();
    p.startLoop();


    return 0;
}
