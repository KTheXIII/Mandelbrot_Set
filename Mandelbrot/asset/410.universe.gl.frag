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

float dist_line(vec2 p, vec2 a, vec2 b) {
    vec2 pa = p - a;
    vec2 ba = b - a;
    float t = clamp(dot(pa, ba) / dot(ba, ba), 0., 1.);
    return length(pa - ba * t);
}

float line(vec2 p, vec2 a, vec2 b) {
    float d = dist_line(p, a, b);
    float m = smoothstep(.03, .01, d);
    float d2 = length(a - b);
    m *= smoothstep(1.2, 0.8, d2) * .5 + smoothstep(.05, .03, abs(d2 - .75));

    return m;
}

float n21(vec2 p) {
    p = fract(p * vec2(432.12, 982.73));
    p += dot(p, p + 93.53);
    return fract(p.x * p.y);
}

vec2 n22(vec2 p) {
    float n = n21(p);
    return vec2(n, n21(p + n));
}

vec2 get_pos(vec2 id, vec2 offs) {
    vec2 n = n22(id + offs) * u_time;
    return offs + sin(n) * .4;
}

float layer(vec2 uv) {
    float m = 0;
    vec2 gv = fract(uv) - .5;
    vec2 id = floor(uv);

    vec2 p[9];

    int i = 0;
    for (float y = -1; y <= 1; y++) {
        for (float x = -1; x <= 1; x++) {
            p[i++] = get_pos(id, vec2(x, y));
        }
    }

    float t = u_time * 10.;
    for (int i = 0; i < 9; i++) {
        m += line(gv, p[4], p[i]);

        vec2 j = (p[i] - gv) * 20.;
        float sparkle = 1. / dot(j, j);

        m += sparkle * (sin(t + fract(p[i].x) * 10.) * .5 + .5);
    }

    m += line(gv, p[1], p[3]);
    m += line(gv, p[1], p[5]);
    m += line(gv, p[7], p[3]);
    m += line(gv, p[7], p[5]);

    return m;
}

void main() {
    vec2 uv = (io_uv - .5) * (u_resolution / u_resolution.y);
    vec2 mouse = (u_mouse.xy / u_resolution.xy) - .5;
    float gradient = uv.y;
    float m = 0;
    float t = u_time * .1;

    float s = sin(t);
    float c = cos(t);
    mat2 rot = mat2(c, -s, s, c);

    uv *= rot;
    mouse *= rot;

    for (float i = 0.; i < 1.; i += 1. / 4.) {
        float z = fract(i + t);
        float size = mix(10., .5, z);
        float fade = smoothstep(0., .5, z) * smoothstep(1., .8, z);

        m += layer(uv * size + i * 43. - mouse) * fade;
    }

    vec3 base = sin(t * vec3(.431, .542, .292)) * .4 + .6;
    vec3 col = m * base;
    col -= gradient * base;

    // if (gv.x > 0.48 || gv.y > 0.48) col.r = 1.;

    o_color = vec4(col, 1.f);
}