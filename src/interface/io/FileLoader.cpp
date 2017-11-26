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
                                                       //   | aiProcess_SortByPType
                                                          | aiProcess_JoinIdenticalVertices
        );
        std::vector<Renderer*> renderers(_scene->mNumMeshes);

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
        float defaultCoords[3]={1.0f, 1.0f, 1.0f};
        float coords[3];
        if (_scene->HasMeshes()) {
            for(int i=0;i<_scene->mNumMeshes;i++){
                const aiMesh *mesh=_scene->mMeshes[i];
                unsigned int faceCount = mesh->mNumFaces;

                auto faceArray =  new unsigned int[mesh->mNumFaces * 3];
               unsigned int faceIndex=0;

                for(int t=0;t<mesh->mNumVertices;t++){
                    LOG("v ["<<t<<"]",mesh->mVertices[t].x<<", "<<mesh->mVertices[t].y<<", "<< mesh->mVertices[t].z);
                }

                for (unsigned int t = 0; t < mesh->mNumFaces; ++t) {
                    const aiFace* face = &mesh->mFaces[t];
                    LOG("f ["<<t<<"]",face->mIndices[0]<<", "<<face->mIndices[1]<<", "<< face->mIndices[2]);

#ifdef MEMCPY
                    memcpy(&faceArray[faceIndex], face->mIndices, 3 * sizeof(unsigned int));
#else
                    faceArray[t * 3] = mesh->mFaces[t].mIndices[0];
                    faceArray[t * 3 + 1] = mesh->mFaces[t].mIndices[1];
                    faceArray[t * 3 + 2] = mesh->mFaces[t].mIndices[2];
#endif

                    faceIndex += 3;
                }

                for (unsigned int t = 0; t < mesh->mNumFaces; t++) {
                    //const aiFace* face = &;

                }

                auto *normals = mesh->mNormals;
                auto *uvs = mesh->mTextureCoords;


                renderers[i]=new Renderer("simple.shader");
                auto *ibo = new IndexBuffer(faceArray, faceCount*3);
                auto *vao = new VertexArray();
                vao->addBuffer(new Buffer(mesh->mVertices,mesh->mNumVertices*3,3),0);
//                vao->addBuffer(new Buffer(uvs,faceCount*3,3),1);
//                vao->addBuffer(new Buffer(normals,faceCount*3,3),2);
                renderers[i]->setModel(ibo,vao);
            }
        }
        return renderers;
    }

}