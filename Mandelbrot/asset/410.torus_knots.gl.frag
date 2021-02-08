/**
 * Torus knot
 *
 * The Art of Code: Torus Knots explained!
 * https://youtu.be/2dzJZx0yngg
 */
#version 410 core
#extension GL_ARB_separate_shader_objects : enable

#define PI     3.14159265359
#define TWO_PI 6.28318530718

#define MAX_STEPS 100
#define MAX_DIST  100.
#define SURF_DIST 0.001

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

float hash21(vec2 p) {
    p = fract(p * vec2(343.95, 817.12));
    p += dot(p, p + 54.84);
    return fract(p.x * p.y);
}

float sd_box(vec3 p, vec3 s) {
    p = abs(p) - s;
    return length(max(p, 0.)) + min(max(p.x, max(p.y, p.z)), 0.);
}

float sd_box2d(vec2 p, vec2 s) {
    p = abs(p) - s;
    return length(max(p, 0.)) + min(max(p.x, p.y), 0.);
}

float get_dist(vec3 p) {
    // float d = sd_box(p, vec3(1));
    float r1 = 1.7;
    float r2 = .3;
    vec2 cp = vec2(length(p.xz) - r1, p.y);

    float a = atan(p.x, p.z);  // Polar angle between -pi and pi
    cp *= rot(a * 2.5);
    cp.y = abs(cp.y) - .4;

    float d = length(cp) - r2;
    // float d = sd_box2d(cp, vec2(.1, .2)) - .05;

    return d * .7;
}

float ray_march(vec3 ro, vec3 rd) {
    float dO = 0.;

    for (int i = 0; i < MAX_STEPS; i++) {
        vec3 p = ro + rd * dO;
        float dS = get_dist(p);
        dO += dS;
        if (dO > MAX_DIST || abs(dS) < SURF_DIST) break;
    }

    return dO;
}

vec3 get_normal(vec3 p) {
    float d = get_dist(p);
    vec2 e = vec2(.001, 0.);

    vec3 n =
        d - vec3(get_dist(p - e.xyy), get_dist(p - e.yxy), get_dist(p - e.yyx));

    return normalize(n);
}

vec3 get_ray_dir(vec2 uv, vec3 p, vec3 l, float z) {
    vec3 f = normalize(l - p);
    vec3 r = normalize(cross(vec3(0, 1, 0), f));
    vec3 u = cross(f, r);
    vec3 c = f * z;
    vec3 i = c + uv.x * r + uv.y * u;
    vec3 d = normalize(i);

    return d;
}

vec3 bg(vec3 rd) {
    float k = rd.y * .5 + .5;
    vec3 col = mix(vec3(1., 117. / 255., 143. / 255.),
                   vec3(168. / 255., 249. / 255., 1.), k);
    return col;
}

void main() {
    vec2 uv = (io_uv - .5) * (u_resolution / u_resolution.y);
    vec2 m = u_mouse.xy / u_resolution.xy;

    vec3 col = vec3(0);

    vec3 ro = vec3(0, 3, -3);
    ro.yz *= rot(-m.y * PI + 1.);
    ro.xz *= rot(-m.x * TWO_PI);

    vec3 rd = get_ray_dir(uv, ro, vec3(0), 1.);

    col += bg(rd);

    float d = ray_march(ro, rd);

    if (d < MAX_DIST) {
        vec3 p = ro + rd * d;
        vec3 n = get_normal(p);
        vec3 r = reflect(rd, n);

        float spec = pow(max(0, r.y), 50.);
        float dif = dot(n, normalize(vec3(1, 2, 3))) * .5 + .5;
        col = mix(bg(r), vec3(dif), .5) + spec;
    }

    col = pow(col, vec3(.4545));  // Gamma correction

    o_color = vec4(col, 1.f);
}