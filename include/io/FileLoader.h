//
// Created by teeebor on 2017-10-25.
//

#pragma once
#include "../utility.h"

#include <string>
#include <vector>
namespace proton{
    class Shader;
    class Renderer;
    class PROTON_API FileLoader {
    public:
        static std::string readFile(const char *path);
        static Shader* readShader(const char *path);
        static std::vector<Renderer*> loadModel(const char *model, const char* material);
    };
}

