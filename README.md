# Mandelbrot set in C++

Basic image generation using [stb](https://github.com/nothings/stb) image loader/writer.

You need to use `--recursive` flag when cloning this repo.

Clone:

```
git clone --recursive https://github.com/KTheXIII/Mandelbrot_set.git
```

## Requirements

  - [premake5](https://github.com/premake/premake-core)

## How to run

Create project file using Premake.

Example: Makefile

```
premake5 gmake
```

### Makefile

Debug mode

```
make
```

Use for building different builds

```
make config=<mode>
```

`<mode>`: **Release**, **Debug**, **Dist**

## Math

z = a + bi

c = x + yi

f(z) = z^2 + c

(a+bi)^2 = a^2 + 2abi - b^2

real = a^2 - b^2 + x

imaginary = 2abi + yi

