//
// Created by teeebor on 2017-10-25.
//

#pragma once

#include <string>
#include <vector>
namespace proton{
    class Shader;
    class Renderer;
    class FileLoader {
    public:
        static std::string readFile(const char *path);
        static Shader* readShader(const char *path);
        static std::vector<Renderer*> loadModel(const char *model);
    };
}

