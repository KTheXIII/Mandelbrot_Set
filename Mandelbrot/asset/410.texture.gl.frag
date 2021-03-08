#version 410 core
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) out vec4 color;

in vec4 io_color;
in vec2 io_uv;

uniform vec4 u_color;
uniform vec2 u_resolution;

uniform sampler2D u_texture0;
uniform sampler2D u_texture1;
uniform sampler2D u_texture2;
uniform sampler2D u_texture4;
uniform sampler2D u_texture5;
uniform sampler2D u_texture6;
uniform sampler2D u_texture7;

void main() {
    vec4 col = texture(u_texture0, io_uv);
    color = col;
}