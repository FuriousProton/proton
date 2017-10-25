//
// Created by teeebor on 2017-10-25.
//

#include "FileLoader.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include <regex>
#include "../graphics/Shader.h"
#include "../../utility.h"

namespace proton {
    std::string FileLoader::readFile(const char *path) {
        FILE *file = fopen(path, "rt");
        fseek(file, 0, SEEK_END);
        auto length = static_cast<unsigned long>(ftell(file));
        auto *data = new char[length + 1];
        memset(data, 0, length + 1);
        fseek(file, 0, SEEK_SET);
        fread(data, 1, length, file);
        fclose(file);

        std::string result(data);
        delete[] data;
        return result;
    }

    Shader *FileLoader::readShader(const char *path) {
        std::ifstream input(path);
        auto *shader = new Shader();
        LOG("SHADER","loading shader from '"<<path<<"'");
        std::string *shaderContent = new std::string[3]{
                "","",""
        };
                ;
        int currentshader=-1;
        std::smatch sm;
        for (std::string line; getline(input, line);) {
            if (std::regex_match("subject", std::regex("#([fragment|vertex|geometry])"))) {
                if (std::regex_match("subject", std::regex("#fragment"))) {
                    currentshader=0;
                    LOG("SHADER","loading fragment shader");
                    continue;
                }
                if (std::regex_match("subject", std::regex("#vertex"))) {
                    currentshader=1;
                    LOG("SHADER","loading vertex shader");
                    continue;
                }
                if (std::regex_match("subject", std::regex("#geometry"))) {
                    currentshader=2;
                    LOG("SHADER","loading geometry shader");
                    continue;
                }
            }
            if(currentshader>-1){
                shaderContent[currentshader]+=line+"\n";
            }
        }
        shader->load(shaderContent);
    }
}