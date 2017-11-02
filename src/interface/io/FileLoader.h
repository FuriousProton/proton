//
// Created by teeebor on 2017-10-25.
//

#pragma once

#include <string>

namespace proton{
    class Shader;
    class FileLoader {
    public:
        static std::string readFile(const char *path);
        static Shader* readShader(const char *path);
    };
}

