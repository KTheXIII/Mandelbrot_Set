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

uniform float u_iterations;
uniform float u_scale;
uniform vec2 u_offset;

uniform sampler2D u_texture;

float mandelbrot(vec2 _z, vec2 _c, vec2 offset, float max_iter) {
    float radius = 2.;
    float r2 = radius * radius;
    vec2 z = _z;
    vec2 c = _c;

    float iterations = 0;
    for (int i = 0; i < max_iter; i++) {
        z = vec2(z.x * z.x - z.y * z.y, 2. * z.x * z.y) + c;

        if (dot(z, z) > r2) break;

        iterations++;
    }

    // float dist = length(z);
    // float frac_iter = (dist - radius) / (r2 - radius);
    // frac_iter = log2(log(dist) / log(radius));
    // iterations -= frac_iter;

    return iterations;
}

void main() {
    vec2 uv = (io_uv - .5) * (u_resolution / u_resolution.y);
    // vec2 uv = io_uv - .5;

    vec3 col = vec3(0);

    float scale = pow(2., u_scale);
    float max_iter = u_iterations != 0 ? u_iterations : 512;

    // Mandelbrot set
    float n = mandelbrot(vec2(0), uv * scale + u_offset, u_offset, max_iter);

    // Julia set
    // float n = mandelbrot(uv * scale, u_offset, u_offset, max_iter);

    if (n < max_iter) {
        float c = sqrt(n / max_iter);
        vec3 color_filter = vec3(.2, .1, .5);
        float freq = 12.;

        col = (sin(color_filter * freq * c - PI / 2.) + 1.) * .5;
    }

    o_color = vec4(col, 1.);
}