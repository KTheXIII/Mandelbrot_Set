#version 410 core
#extension GL_ARB_separate_shader_objects : enable

#define PI 3.14159265359
#define TWO_PI 6.28318530718

layout(location = 0) out vec4 o_color;

in vec4 io_color;
in vec2 io_uv;

uniform float u_time;
uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform vec4 u_color;

uniform sampler2D u_texture;

float n21(vec2 p) { return fract(sin(p.x * 1514.3 + p.y * 828.74) * 5482.61); }

float circle(in vec2 uv, in float radius) {
    return 1. - smoothstep(radius - (radius * .01), radius + (radius),
                           dot(uv, uv) * 4.0);
}

void main() {
    vec2 uv = (io_uv - .5) * (u_resolution / u_resolution.y);
    vec2 mouse = (u_mouse.xy / u_resolution.xy) - .5;

    uv *= 10.;

    vec2 g_uv = fract(uv) - .5;
    vec2 g_id = floor(uv);

    float ampl = .35;
    float t = u_time;
    float n = n21(g_id);
    float n2 = fract(n * 82.419);
    float c = 0.;
    c = circle(g_uv - vec2(cos(t * n) * ampl, sin(t * n2) * ampl), 0.01);

    vec3 col = vec3(c);
    //    col.rg = g_uv;
    //    if(g_uv.x > .48 || g_uv.y > .48) col.r = 1.;

    o_color = vec4(col, 1.);
}