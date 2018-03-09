//
// Created by teeebor on 2017-10-24.
//

#pragma once

#include "utility.h"
#include <vector>
#include <map>
struct DisplaySettings;
namespace proton{
    class Display;
    class Entity;
}
class PROTON_API Proton {
private:
    proton::Display *mDisplay;
    std::vector<proton::Entity*> mEntities;
    static Proton *activeInstance;
public:
    static std::map<int, int> keyStates;
    /**
     * Main loop
     */
    void startLoop();
    static void errorcheck(const char* label);
    void loopChilds(proton::Entity *e);
    /**
     * Creating display
     * @param dSettings Reference to the display configuration structure
     */
    bool createDisplay(DisplaySettings &dSettings);
    void cleanUp();
};

