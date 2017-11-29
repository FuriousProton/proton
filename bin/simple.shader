#vertex
#version 410 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 textureCoords;
layout (location = 2) in vec3 normals;
layout (location = 3) in vec3 vertex_color;

uniform struct{
    mat4 model;
    mat4 view;
    mat4 projection;
} mvp;

out vec3 out_color;

void main(){
//    out_color=vertex_color;
    gl_Position = mvp.projection  *
                                         mvp.view *
                                         mvp.model*
                                         vec4(position,1);
    out_color=(mvp.model*vec4(position,1)).xyz;

}


#fragment
#version 410 core

in vec3 out_color;

out vec4 color;

void main(){
    float c = out_color.z*4;
//    color = normalize(vec4(c,c,c,1.0));
//    color = vec4(1.0);
   color = vec4(normalize(out_color).xyz,1.0);
}