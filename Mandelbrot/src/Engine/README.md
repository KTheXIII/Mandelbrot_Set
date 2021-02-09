# Engine

Notes for Engine.

The engine is not platform specific since it is using GLFW and OpenGL. There are no abstraction layer for switching to different graphics API.

## Steps to Renderer

Step 1: Build Render API

Step 2: Build Renderer

These steps have overlaps.

## Render API (API/Platform specific)

Render API is your implementation of graphics API like Vulkan, DirectX, Metal and OpenGL. These graphics API have overlap features and some have great features that other might not have.

- Render Context
- Swap chain
- Framebuffer
- Vertex Buffer
- Index/Element Buffer
- Texture
- Shader
- States
- Pipelines
- Render passes

## Renderer (API/platform agnostic)

Renderer uses your Render API.

- 2D & 3D Renderer
  - Forward, deferred, etc.
- Scene Graph
- Sorting
- Culling
- Materials → Shaders
- LOD
- Animation
- Camera
- VFX
- PostFX
- Other things
  - (eg. reflections, ambient occlusion)

## Texture and Images

### Texture

In OpenGL you create a texture buffer like this.

```cpp
glGenTextures(1, &buffer); // buffer is your uint32_t variable.
```

In `buffer` you'll get and ID where the OpenGL has created your buffer object. This will be use for example bind your texture and upload your data to the GPU.


To bind the texture you'll use

```cpp
glBindTexture(GL_TEXTURE_2D, buffer);
```

`GL_TEXTURE_2D` tells OpenGL what type of data it is receiving. `buffer` is your buffer object id, which you've generated with `glGenTextures`.

You can tell OpenGL which slot it needs to bind to by using this command.

```cpp
glActiveTexture(GL_TEXTURE0); // Bind onto texture slot 0
```

You do this before you call `glBindTexture` function. `GL_TEXTURE0` is the zero slot, you increment the number to get to different slots.

You can use the texture slot in your shader program like this

```glsl
uniform sampler2D texture0; // GL_TEXTURE0
uniform sampler2D texture1; // GL_TEXTURE1

void main() {
    color = mix(texture(texture0, uv), texture(texture1, uv), 0.5); // Mix between 2 textures at 50%
}
```