//
// Created by teeebor on 2017-11-29.
//

#pragma once

#include "Shader.h"
#include <vector>
#include "../utility.h"
#include <glm/gtc/type_ptr.hpp>

struct PROTON_API Uniform {
    unsigned int mID;
    Uniform(const char* name, proton::Shader *s);
    virtual void load(proton::Shader *s);
};

struct PROTON_API Uniform1i : public Uniform {
    int value;
    Uniform1i(const char *name, proton::Shader *s, int v);
    void load(proton::Shader *s) override;
};
struct PROTON_API Uniform1f : public Uniform {
    float value;
    Uniform1f(const char *name, proton::Shader *s, float v);
    void load(proton::Shader *s) override;
};
struct PROTON_API Uniform2f : public Uniform {
    glm::vec2 value;
    Uniform2f(const char *name, proton::Shader *s, glm::vec2& v);
    void load(proton::Shader *s) override;
};
struct PROTON_API Uniform3f : public Uniform {
    glm::vec3 value;
    Uniform3f(const char *name, proton::Shader *s, glm::vec3& v);
    void load(proton::Shader *s) override;
};
struct PROTON_API Uniform4f : public Uniform {
    glm::vec4 value;
    Uniform4f(const char *name, proton::Shader *s, glm::vec4& v);
    void load(proton::Shader *s) override;
};
struct PROTON_API UniformMat4 : public Uniform {
    glm::mat4 value;

    UniformMat4(const char *name, proton::Shader *s, glm::mat4 &v);

    void load(proton::Shader *s) override;
};