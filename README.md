# OpenGL Renderer

A modern OpenGL graphics application built with C++, SDL3, GLEW, GLM, and ImGui. The project demonstrates shader-based rendering, object animation, interactive camera controls, and real-time color manipulation using the programmable graphics pipeline.

## Overview

This project renders multiple animated cube instances using modern OpenGL. Geometry is uploaded to GPU buffers and rendered using custom GLSL shaders while an interactive camera allows exploration of the scene.

The application was developed using a course-provided framework for window creation, event handling, and OpenGL initialization. My work focuses on implementing the rendering logic, animation, shader integration, and user interaction.

## My Contributions

My implementation includes:

- Creating and uploading geometry using VAOs, VBOs, and index buffers
- Implementing the rendering pipeline with custom GLSL shaders
- Rendering multiple cube instances with individual world transformations
- Animating object movement and color transitions
- Integrating an interactive camera
- Implementing real-time color selection using ImGui
- Managing GPU resources and rendering state

## Features

- Modern OpenGL rendering pipeline
- Vertex and fragment shaders (GLSL)
- Vertex Buffer Objects (VBO)
- Vertex Array Objects (VAO)
- Indexed rendering
- Interactive 3D camera
- Animated object transformations
- Real-time color animation
- ImGui integration
- OpenGL debug callback support

## Technologies

- C++
- OpenGL
- GLSL
- SDL3
- GLEW
- GLM
- ImGui

## Project Structure

```text
OpenGL-Renderer/
│
├── main.cpp
├── MyApp.cpp
├── MyApp.h
├── Vert_PosCol.vert
├── Frag_PosCol.frag
└── README.md
```

## Rendering Pipeline

The application follows the modern OpenGL rendering pipeline:

1. Create an SDL window and OpenGL context.
2. Initialize OpenGL and required libraries.
3. Compile and link the GLSL shaders.
4. Upload mesh data to GPU buffers.
5. Configure vertex attributes.
6. Update object transformations each frame.
7. Render animated cube instances.
8. Display an ImGui interface for interactive controls.

## Graphics Features

The renderer demonstrates:

- GPU-based rendering
- Indexed mesh rendering
- World transformations
- Camera view and projection matrices
- Per-object animation
- Color interpolation
- Real-time GUI interaction

## Controls

| Input | Action |
|--------|--------|
| Mouse | Rotate camera |
| Mouse Wheel | Zoom |
| F1 | Toggle wireframe mode |
| Ctrl + F5 | Reload shaders |
| ImGui Color Picker | Change animation color |

## Learning Objectives

This project demonstrates practical concepts in modern computer graphics, including:

- Shader programming
- GPU resource management
- Matrix transformations
- Camera systems
- Interactive rendering
- Real-time graphics programming

## License

This project is licensed under the **Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License**.

https://creativecommons.org/licenses/by-nc-nd/4.0/
