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
#include "engine/component/Transform.h"
#include "engine/component/DemoComponent.h"
#include "interface/io/FileLoader.h"

//#define CHAI

#ifdef CHAI
#include <chaiscript/chaiscript.hpp>
#include <chaiscript/chaiscript_stdlib.hpp>
std::string helloWorld(const std::string &t_name) {
    return "Hello " + t_name + "!";
}
#endif
int main()
{
    using namespace proton;

#ifdef CHAI

    chaiscript::ChaiScript chai;
    chai.add(chaiscript::fun(&helloWorld), "helloWorld");
    chai.eval(R"(
    puts(helloWorld("Bob"));
  )");

#endif

    DisplaySettings dSettings;
    dSettings.title="Game";
    Proton p{};
    auto *scene = new Scene();
    if(p.createDisplay(dSettings)) {
        auto *c = new Camera(800, 600, 70, .01f, 1000);
        auto *e = new Entity();
        auto *r = new Renderer("simple.shader");
        //@TODO culling bugging for some reason
        scene->addEntity(c);
#define IBO_LEN 3
        unsigned int indexes[IBO_LEN] = {
                0, 2, 1
        };
        IndexBuffer ibo(indexes, IBO_LEN);
        VertexArray vao;
#define VBO_LEN 9
  /*      float vert[VBO_LEN] = {
                -0.5f, 0,-10,
                0.5f, 0, -10,
                0, 0.5f, -10
        };
        float col[VBO_LEN] = {
                1, 0, 0,
                0, 1, 0,
                0, 0, 1
        };

     Buffer verticles(vert, VBO_LEN, 3);
     Buffer colors(col, VBO_LEN, 3);
     vao.addBuffer(&verticles, 0);
     vao.addBuffer(&colors, 3);
    r->setModel(&ibo, &vao);*/

        std::vector<Renderer *> renderer=FileLoader::loadModel("cube.obj");
        e->addComponent(renderer[0]);

        c->transform().move(0,0,10);
        e->addComponent(new DemoComponent());
      //  e->transform().rotate(glm::vec3(90,0,0));
        scene->addEntity(e);
        c->setCulling(true);
        scene->activate();
        p.startLoop();
        p.cleanUp();
    }
    return 0;
}
