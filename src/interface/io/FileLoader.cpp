//
// Created by teeebor on 2017-10-25.
//

#include "FileLoader.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include <regex>

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags


#include "../graphics/Shader.h"
#include "../../utility.h"
#include "../graphics/VertexArray.h"
#include "../graphics/Buffer.h"
#include "../../engine/component/Renderer.h"
#include "../graphics/IndexBuffer.h"

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
        shader->load(shaderContent);
        return shader;
    }

    std::vector<Renderer*> FileLoader::loadModel(const char *model) {
        unsigned int numFaces = 0;
        Assimp::Importer importer;
        const aiScene *_scene = importer.ReadFile(model,
                                                  aiProcess_CalcTangentSpace
                                                           | aiProcess_Triangulate
                                                          | aiProcess_SortByPType
                                                          | aiProcess_JoinIdenticalVertices
        );
        std::vector<Renderer*> renderers;
        if(_scene){

//Material and texture loading
/*        if (_scene->HasMaterials()) {
            for(int i=0;i<_scene->mNumMaterials;i++){
                aiMaterial *material=_scene->mMaterials[i];
            }
        }
        if (_scene->HasTextures()) {
            for (int i = 0; i < _scene->mNumTextures; i++) {
                aiTexture *texture = _scene->mTextures[i];
            }
        }
*/
            //Loading model
            std::vector<unsigned int> indices;
            if (_scene->HasMeshes()) {
                for(int i=0;i<_scene->mNumMeshes;i++){
                    const aiMesh *mesh=_scene->mMeshes[i];
                    unsigned int faceCount = mesh->mNumFaces;

                    auto faceArray =  new unsigned int[mesh->mNumFaces * 3];
                    unsigned int faceIndex = 0;

                    for (unsigned int t = 0; t < mesh->mNumFaces; t++) {
                        const aiFace* face = &mesh->mFaces[t];
                        memcpy(&faceArray[faceIndex], face->mIndices,3 * sizeof(unsigned int));
                        faceIndex += 3;
                    }


                    auto *r=new Renderer("simple.shader");
                    auto *ibo = new IndexBuffer(faceArray, faceCount*3);
                    auto *vao = new VertexArray();
                    int count=mesh->mNumVertices*3;
                    vao->addBuffer(new Buffer(mesh->mVertices,count,3),0);
//                    if(mesh->HasNormals()){
//                        vao->addBuffer(new Buffer(mesh->mNormals,count,3),1);
//                    }
//                    if(mesh->HasTextureCoords(0)){
//                        vao->addBuffer(new Buffer(mesh->mTextureCoords,count,3),2);
//                    }
                    r->setModel(ibo,vao);
                    renderers.push_back(r);
                }
            }
        }else{
            LOG("MODEL LOADER","Faliled to load model");
        }
        return renderers;
    }

}