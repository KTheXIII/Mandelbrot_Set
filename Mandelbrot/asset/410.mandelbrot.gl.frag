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

float mandelbrot(vec2 uv, vec2 offset, float max_iter) {
    float r2 = 2. * 2.;
    vec2 z = vec2(0);
    vec2 c = uv + offset;

    float iterations = 0;
    for (int i = 0; i < max_iter; i++) {
        z = vec2(z.x * z.x - z.y * z.y, 2. * z.x * z.y) + c;
        if (dot(z, z) > r2) break;
        iterations++;
    }

    return iterations;
}

void main() {
    vec2 uv = (io_uv - .5) * (u_resolution / u_resolution.y);
    // vec2 uv = io_uv - .5;

    vec3 col = vec3(0);

    float scale = 4.;
    float max_iter = 512.;
    float n = mandelbrot(uv * scale, vec2(0.), max_iter);

    if (n < max_iter) {
        float c = sqrt(n / max_iter);
        vec3 color_filter = vec3(.2, .1, .5);
        float freq = 12.;

        col = (sin(color_filter * freq * c - PI / 2.) + 1.) * .5;
    }

    o_color = vec4(col, 1.);
}