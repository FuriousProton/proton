
#include "../include/component/Renderer.h"
#include "../include/utility.h"
#include "../include/DisplaySettings.h"
#include "../include/Proton.h"
#include "../include/entity/Entity.h"
#include "../include/Scene.h"
#include "../include/interface/IndexBuffer.h"
#include "../include/interface/VertexArray.h"
#include "../include/interface/Buffer.h"
#include "../include/entity/Camera.h"
#include "../include/component/Transform.h"
#include "engine/component/DemoComponent.h"
#include "../include/io/FileLoader.h"
#include "engine/component/Move.h"

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
        scene->addEntity(c);

        c->transform().move(0,5,10);
        e->addComponent(new DemoComponent());
        c->addComponent(new Move());
      //  e->transform().rotate(glm::vec3(90,0,0));
        scene->addEntity(e);
        c->setCulling(false);
        c->setBlend(false);
        scene->activate();
        p.startLoop();
        p.cleanUp();
    }
    return 0;
}
