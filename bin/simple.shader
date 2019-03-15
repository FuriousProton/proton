#vertex

#version 330 core

layout (location = 0) in vec3 position;
uniform struct {
    mat4 model;
    mat4 view;
    mat4 projection;
} mvp;

void main()
{
    gl_Position = (mvp.projection * mvp.view * mvp.model ) * vec4(position,1.0);
}


#fragment

#version 330 core
in float coord;
in vec3 pos;
void main()
{
  gl_FragColor = vec4(1.0, 1.0, 0.0, 1.0);
}
