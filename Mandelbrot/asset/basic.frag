#version 410 core
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) out vec4 color;

void main() {
    color = vec4(.1, .86, .99, 1.0);
}