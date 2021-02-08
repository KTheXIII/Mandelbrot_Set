/**
 * Drawing firework using shaders.
 *
 * The Art of Code: Coding a fireworks effect
 * https://youtu.be/xDxAnguEOn8
 */
#version 410 core
#extension GL_ARB_separate_shader_objects : enable

#define PI     3.14159265359
#define TWO_PI 6.28318530718

#define NUM_EXPLOSIONS 8.
#define NUM_PARTICLES  100.

layout(location = 0) out vec4 o_color;

in vec4 io_color;
in vec2 io_uv;

uniform float u_time;
uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform vec4 u_color;

uniform sampler2D u_texture;

vec2 hash12(float t) {
    float x = fract(sin(t * 912.49) * 458.5);
    float y = fract(sin((t + x) * 382.49) * 831.5);

    return vec2(x, y);
}

vec2 hash12_polar(float t) {
    float a = fract(sin(t * 912.49) * 458.5) * TWO_PI;
    float d = fract(sin((t + a) * 382.49) * 831.5);

    return vec2(sin(a), cos(a)) * d;
}

float explosion(vec2 uv, float t) {
    float sparks = 0.;
    for (float i = 0.; i < NUM_PARTICLES; i++) {
        vec2 dir = hash12_polar(i + 1.) * .5;
        float d = length(uv - dir * t);

        float brightness = mix(0.0005, 0.001, smoothstep(.05, .0, t));

        brightness *= sin(t * 20. + i) * .5 + .5;
        brightness *= smoothstep(1., .5, t);

        sparks += brightness / d;
    }

    return sparks;
}

void main() {
    vec2 uv = (io_uv - .5) * (u_resolution / u_resolution.y);

    vec3 col = vec3(0);

    for (float i = 0.; i < NUM_EXPLOSIONS; i++) {
        float t = u_time + i / NUM_EXPLOSIONS;
        float ft = floor(t);
        vec3 color = sin(5. * vec3(.32, .54, .23) * ft) * .3 + .7;

        vec2 offs = hash12(i + 1. + ft) - .5;
        offs *= vec2(u_resolution.x / u_resolution.y, 1.);

        col += explosion(uv - offs, fract(t)) * color;
        // col += .001 / length(uv - offs);
    }

    col *= 2.;
    o_color = vec4(col, 1.f);
}