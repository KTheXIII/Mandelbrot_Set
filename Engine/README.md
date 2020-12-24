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
