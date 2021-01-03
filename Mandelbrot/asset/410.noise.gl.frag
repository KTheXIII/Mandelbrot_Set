#version 410 core
#extension GL_ARB_separate_shader_objects : enable

#define PI 3.14159265359
#define TWO_PI 6.28318530718

#define MAX_STEPS 100
#define MAX_DIST 100.
#define SURF_DIST 0.001

layout(location = 0) out vec4 o_color;

in vec4 io_color;
in vec2 io_uv;

uniform float u_time;
uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform vec4 u_color;

uniform sampler2D u_texture;

/**
 * Get Noise
 */
float n21(vec2 p) { return fract(sin(p.x * 1514.3 + p.y * 828.74) * 5482.61); }

float smooth_noise(vec2 uv) {
    vec2 lv = fract(uv);
    vec2 id = floor(uv);

    lv = lv * lv * (3. - 2. * lv);

    float bl = n21(id);
    float br = n21(id + vec2(1, 0));
    float b = mix(bl, br, lv.x);

    float tl = n21(id + vec2(0, 1));
    float tr = n21(id + vec2(1, 1));
    float t = mix(tl, tr, lv.x);

    return mix(b, t, lv.y);
}

float smooth_noise_layered(vec2 uv) {
    float c = smooth_noise(uv * 4.);
    c += smooth_noise(uv * 8.) * .5;
    c += smooth_noise(uv * 16.) * .25;
    c += smooth_noise(uv * 32.) * .125;
    c += smooth_noise(uv * 64.) * .0625;

    return c / 2.;
}

void main() {
    vec2 uv = (io_uv) * (u_resolution / u_resolution.y);

    uv += u_time * .1;
    float c = smooth_noise_layered(uv);

    vec3 col = vec3(c);

    o_color = vec4(col, 1.);
}