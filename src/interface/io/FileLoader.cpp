//
// Created by teeebor on 2017-10-25.
//

#include "../../../include/io/FileLoader.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include <regex>

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

#include <stdio.h>  /* defines FILENAME_MAX */
// #define WINDOWS  /* uncomment this line to use it for windows.*/
#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

#include <glbinding/gl/gl.h>
#include<iostream>

#include "../../../include/interface/Shader.h"
#include "../../../include/utility.h"
#include "../../../include/interface/VertexArray.h"
#include "../../../include/interface/Buffer.h"
#include "../../../include/component/Renderer.h"
#include "../../../include/interface/IndexBuffer.h"
#include "../../../include/interface/Texture.h"
#include "../../../include/Proton.h"

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
        Shader *shader = new Shader();
        LOG("SHADER", "loading shader from '" << path << "'");
        std::string *shaderContent = new std::string[3]{
                "", "", ""
        };
        int currentshader = -1;
        std::smatch sm;
        std::string line;
        while (input && getline(input, line)) {
            if (line.length() == 0) continue;
            if (std::regex_match(line, std::regex("#vertex"))) {
                currentshader = 0;
                LOG("SHADER", "loading vertex shader");
                continue;
            }
            if (std::regex_match(line, std::regex("#fragment"))) {
                currentshader = 1;
                LOG("SHADER", "loading fragment shader");
                continue;
            }
            if (std::regex_match(line, std::regex("#geometry"))) {
                currentshader = 2;
                LOG("SHADER", "loading geometry shader");
                continue;
            }
            if (currentshader > -1) {
                shaderContent[currentshader] += line + "\n";
            }
        }
        Proton::errorcheck("before shader load");

        shader->load(shaderContent);
        Proton::errorcheck("shader load");

        return shader;
    }

    std::vector<Renderer *> FileLoader::loadModel(const char *model, const char* material) {
        unsigned int numFaces = 0;
        Assimp::Importer importer;

        const aiScene *_scene = importer.ReadFile(model,
                                                  aiProcess_GenSmoothNormals |
                                                  aiProcess_CalcTangentSpace
                                                  | aiProcess_Triangulate
                                                  | aiProcess_SortByPType
                                                  | aiProcess_JoinIdenticalVertices
        );
        std::vector<Renderer *> renderers;
        if (_scene) {
            char buff[FILENAME_MAX];
            GetCurrentDir( buff, FILENAME_MAX );
            std::string current_working_dir(buff);

            std::string path =  std::regex_replace (model,std::regex("([a-zA-Z0-9\\.\\_\\-\\s]+)\\.(OBJ|FBX|STL|obj|fbx|stl)$"),"/");
            LOG("DIR",current_working_dir);
            Proton::errorcheck("before texture load");
            Texture *textures[_scene->mNumTextures];
            if (_scene->HasMaterials()) {
                for (unsigned int i = 0; i < _scene->mNumMaterials; i++) {
                    const aiMaterial *material = _scene->mMaterials[i];
                    int USECOLOR = 0;
                    aiString texturePath;
                    unsigned int numTextures = material->GetTextureCount(aiTextureType_DIFFUSE);   // always 0

                    if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0 &&
                        material->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath) == AI_SUCCESS) {
                        std::cout << texturePath.C_Str() << std::endl;
                        std::string s =  path;
                        s.append(texturePath.C_Str());
                        textures[i] = new Texture(s.c_str(), 0);
                        LOG("TEXTURE",textures[i]->getTextureID());
                        Proton::errorcheck("texture load");
                    }

                }
            }

            //Loading model
            std::vector<unsigned int> indices;
            if (_scene->HasMeshes()) {
                for (int i = 0; i < _scene->mNumMeshes; i++) {
                    const aiMesh *mesh = _scene->mMeshes[i];
                    unsigned int faceCount = mesh->mNumFaces;

                    auto faceArray = new unsigned int[mesh->mNumFaces * 3];
                    unsigned int faceIndex = 0;

                    for (unsigned int t = 0; t < mesh->mNumFaces; t++) {
                        const aiFace *face = &mesh->mFaces[t];
                        memcpy(&faceArray[faceIndex], face->mIndices, 3 * sizeof(unsigned int));
                        faceIndex += 3;
                    }


                    auto *r = new Renderer(material);
                    Proton::errorcheck("shader");

                    auto *ibo = new IndexBuffer(faceArray, faceCount * 3);
                    Proton::errorcheck("ibo");
                    auto *vao = new VertexArray();

                    Proton::errorcheck("vao");
                    int count = mesh->mNumVertices * 3;
                    vao->addBuffer(new Buffer(mesh->mVertices, count, 3), 0);
                    Proton::errorcheck("verticle");
                    if (mesh->HasNormals()) {
                        vao->addBuffer(new Buffer(mesh->mNormals, count, 3), 2);
                        Proton::errorcheck("normal");

                    }
                    if (mesh->HasTextureCoords(0)) {
                        vao->addBuffer(new Buffer(mesh->mTextureCoords[0], mesh->mNumVertices*3, 3), 1);
                        Proton::errorcheck("texture");

                    }
                    int textureID = mesh->mMaterialIndex;
                    if (textureID >= 0 && textureID < _scene->mNumTextures) {
                        r->setTexture(textures[textureID]);
                        Proton::errorcheck("texture_load");
                    }
                    r->setModel(ibo, vao);
                    renderers.push_back(r);

                    Proton::errorcheck("LOAD");
                }
            }
        } else {
            LOG("MODEL LOADER", "Faliled to load model");
        }
        return renderers;
    }

}