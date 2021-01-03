#version 410 core
#extension GL_ARB_separate_shader_objects : enable

#define PI 3.14159265359
#define TWO_PI 6.28318530718

layout(location = 0) out vec4 out_color;

in vec4 io_color;
in vec2 io_uv;

uniform float u_time;
uniform vec2 u_resolution;
uniform vec4 u_color;

uniform sampler2D u_texture;

void main() {
    vec2 uv = io_uv;

    vec3 color = vec3(0.);
    vec3 rgb_comp = vec3(.3, 0.1, 0.5);
    float freq = 12.;

    float f = length(uv);

    color = (sin((rgb_comp * freq * f - PI / 2.)+ (u_time * 4)) + 1.) * 0.5;
    out_color = vec4(color, 1.f);
}