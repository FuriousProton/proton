//
// Created by teeebor on 2017-11-29.
//

#include "../../../include/interface/Texture.h"
#include "../../../include/utility.h"
#include "../../../include/Proton.h"

#define STB_IMAGE_IMPLEMENTATION

#include <stb_image.h>

proton::Texture::Texture(const char *path, int l) {
    using namespace gl;

    LOG("LOADING TEXTURE", path);
    if (l >= 0 && l < 32) {
        location = TEXTURE_ENUMS[l];
    }
    Proton::errorcheck("before texture init");

    int width, height, nrChannels;
    unsigned char *data;
    data = stbi_load(path, &width, &height, &nrChannels, 0);

    if(data && nrChannels>1){
        LOG("Texture size: ", width << "; " << height << " channels: " << nrChannels);
        glGenTextures(1, &textureID);
        Proton::errorcheck("after texture init");

        bind();
        Proton::errorcheck("after texture bind");
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        Proton::errorcheck("after texture align");

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        LOG("INFO", "after load");
        Proton::errorcheck("after texture teximage");
        stbi_image_free(data);

        Proton::errorcheck("after texture init  load");
    }
    else{
        LOG("TEXTURE ERROR", path << " Cannot be loaded");
    }
}

proton::Texture::~Texture() {
    if (0 > textureID) {
        gl::glDeleteTextures(1, &textureID);
    }
}

void proton::Texture::bind() {
    using namespace gl;
    if (0 <= textureID) {
        glActiveTexture(location);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
}

void proton::Texture::unbind() {
    using namespace gl;
    glBindTexture(GL_TEXTURE_2D, 0);
}

unsigned int proton::Texture::getTextureID() {
    return textureID;
}
