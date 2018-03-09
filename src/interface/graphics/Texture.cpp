//
// Created by teeebor on 2017-11-29.
//

#include "../../../include/interface/Texture.h"
#include "../../../include/utility.h"
#include "../../../include/Proton.h"
#include <SOIL.h>

proton::Texture::Texture(const char *path, int l) {
    using namespace gl;


    LOG("LOADING TEXTURE",path);
    if(l>=0 && l<32){
        location=TEXTURE_ENUMS[l];
    }
    int width=0, height=0;
    Proton::errorcheck("before texture init");
    unsigned char* image = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGB);


    glGenTextures(1,&textureID);
    Proton::errorcheck("after texture init");

    bind();
    Proton::errorcheck("after texture bind");
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    Proton::errorcheck("after texture align");
    LOG("width",width);
    LOG("height",height);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

    Proton::errorcheck("after texture teximage");
    SOIL_free_image_data(image);

    Proton::errorcheck("after texture imiz  load");
    if (0 > textureID)
    {
        LOG("TEXTURE ERROR",SOIL_last_result());
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
