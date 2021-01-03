#version 410 core
#extension GL_ARB_separate_shader_objects : enable

#define PI 3.14159265359
#define TWO_PI 6.28318530718
#define NUM_LAYERS 8.

layout(location = 0) out vec4 o_color;

in vec4 io_color;
in vec2 io_uv;

uniform float u_time;
uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform vec4 u_color;

uniform sampler2D u_texture;

mat2 rot(float a) {
    float s = sin(a), c = cos(a);
    return mat2(c, -s, s, c);
}

float star(vec2 uv, float flare) {
    float d = length(uv);
    float m = .02 / d;

    float rays = max(0., 1. - abs(uv.x * uv.y * 1000.));
    m += rays * flare;
    uv *= rot(PI / 4.);
    rays = max(0., 1. - abs(uv.x * uv.y * 1000.));
    m += rays * .3 * flare;

    m *= smoothstep(1., 0.2, d);
    return m;
}

float hash21(vec2 p) {
    p = fract(p * vec2(743.42, 843.24));
    p += dot(p, p + 58.17);
    return fract(p.x * p.y);
}

vec3 star_layer(vec2 uv) {
    vec3 col = vec3(0.);

    vec2 gv = fract(uv) - .5;
    vec2 id = floor(uv);

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            vec2 offs = vec2(j, i);

            float n = hash21(id + offs);  // Random between 0 and 1
            float size = fract(n * 472.38);

            float star = star(gv - offs - vec2(n, fract(n * 51.)) + .5,
                              smoothstep(.95, 1., size));

            vec3 color =
                sin(vec3(.2, .3, .9) * fract(n * 1392.3) * 431.2) * .5 + .5;
            color = color * vec3(1., 0.5, 1. + size);

            star *= sin(u_time * 3. + n * 848.) * .5 + .5;

            col += star * size * color;
        }
    }

    return col;
}

void main() {
    vec2 uv = (io_uv - .5) * (u_resolution / u_resolution.y);
    vec2 mouse = (u_mouse.xy / u_resolution.xy) - .5;
    uv *= 1.;
    float t = u_time * .1;

    uv *= rot(t);
    mouse *= rot(t);

    vec3 col = vec3(0.);

    for (float i = 0.; i < 1.; i += 1. / NUM_LAYERS) {
        float depth = fract(i + t);
        float scale = mix(20., .5, depth);
        float fade = depth * smoothstep(1., .9, depth);

        col += star_layer(uv * scale + i * 34. - mouse) * fade;
    }

    o_color = vec4(col, 1.f);
}