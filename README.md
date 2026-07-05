# 2D/3D Game of Chess using C++ and OpenGL
The goal of this project is to create a 3D playable chess game using <u>**C++**</u> and the <u>**OpenGL**</u> graphics API.
While many modern rendering engines (such as Unreal Engine and Unity) do all of the low-level rendering for developers, it's incredibly important to recognise *how* every polygon is actually rendered. This project showcases how low-level graphics API's can be interfaced with to create something just as realistic as a modern-day engine. Additionally, this project showcases all of the minor aspects of 3D game development and rendering that most developers take for granted.

This project will start out as a 2D game of chess, simplifying the rendering process and allowing game systems to be developed quickly, but will eventually expand to be a fully 3D game of chess utilising 3D models and Physically Based Rendering (PBR) techniques. The purpose of this is to create a project where gameplay systems are totally independent from the rendering pipeline, and to show how both 2D and 3D are fundamentally handled in the same way.

## Languages Used
| Name | Purpose |
| --- | --- |
| C++ | All source code. |
| GLSL | Used to write shaders. |
| C | For implemented libraries / modules. |


## Technologies Used
| Name | Purpose |
| --- | --- |
| OpenGL | A cross-platform API for rendering 2D and 3D graphics. |
| GLFW3 | Used for window management and creation. |
| GLAD | Initialising and managing OpenGL function pointers at runtime. |
| GLM | A math library used for vectors, transformations, matrices, etc. |
| STB | Primarily used for loading textures. |


## Resources Used
- https://learnopengl.com/Getting-started
- https://www.glfw.org/docs/latest/
- https://github.com/lszl84/glfw_opengl_cmake_template
