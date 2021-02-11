# Mandelbrot set in C++

Mandelbrot set in C++ with CPU compute and GPU compute. You can switch between the mode and see which one is faster and which one have more precision.

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

For generating projects you need premake. Premake can generate the project for make, Xcode, Visual Studio, etc.

  - [premake5](https://github.com/premake/premake-core)

**Windows**

For compiling on Windows I recommend you to use 

  - [Visual Studio](https://visualstudio.microsoft.com/)

**macOS**

On macOS you'll need to install Xcode which will get you the C++ compiler.

## How to run

Create project file using Premake.

Example: Makefile

```
premake5 gmake2
```

To run the program in debug mode you'll need to be inside the directory where `src` directory lives.

```shell
Mandelbrot_set
├── bin
├── Mandelbrot  ← cd into this directory
│   ├── asset
│   ├── src
│   └── vendor
├── obj
├── .clang-format
├── .gitignore
├── .gitmodules
├── LICENSE
├── premake5.lua
└── README.md
```

^ The directory structure should look something like this when you've compiled the program.

```
cd Mandelbrot
```

The binary you can execute is in the `bin`, in some folder, depending on the mode and platform. The binary should have the name `Mandelbrot`

```
../bin/Debug-*/Mandelbrot/Mandelbrot
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

`<mode>`: **release**, **debug**

The release mode will copy over the asset to the output binary so you don't have to worry about where you launch the program from. This only applies of course if the asset folder lives in the same directory as the binary.

## Math

z = a + bi

c = x + yi

f(z) = z^2 + c

(a+bi)^2 = a^2 + 2abi - b^2

real = a^2 - b^2 + x

imaginary = 2abi + yi

## Sample Image

![Mandelbrot set image in color](https://i.imgur.com/HJZMNl7.png)