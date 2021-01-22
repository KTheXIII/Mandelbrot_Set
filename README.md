# Mandelbrot set in C++

Basic image generation using [stb](https://github.com/nothings/stb) image loader/writer.

You need to use `--recursive` flag when cloning this repo.

Clone:

```
git clone --recursive https://github.com/KTheXIII/Mandelbrot_set.git
```

If you didn't pull with --recursive then you can do this command to pull the submodules

```
git submodule update --init --recursive
```

## Requirements

  - [premake5](https://github.com/premake/premake-core)

## How to run

Create project file using Premake.

Example: Makefile

```
premake5 gmake2
```

To the program you need to be inside Mandelbrot directory and run the executable from there. This is because the asset folder is in it.

```
cd Mandelbrot
```

```
../bin/<executable_path>
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

`<mode>`: **Release**, **Debug**

## Math

z = a + bi

c = x + yi

f(z) = z^2 + c

(a+bi)^2 = a^2 + 2abi - b^2

real = a^2 - b^2 + x

imaginary = 2abi + yi

## Sample Image

![Mandelbrot set image in color](https://i.imgur.com/HJZMNl7.png)