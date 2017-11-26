//
// Created by teeebor on 2017-10-24.
//

#pragma once

#include <vector>
struct DisplaySettings;
namespace proton{
    class Display;
    class Entity;
}
class Proton {
private:
    proton::Display *mDisplay;
    std::vector<proton::Entity*> mEntities;
public:
    /**
     * Main loop
     */
    void startLoop();

    void loopChilds(proton::Entity *e);
    /**
     * Creating display
     * @param dSettings Reference to the display configuration structure
     */
    bool createDisplay(DisplaySettings &dSettings);
    void cleanUp();
};

