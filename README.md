# 2D Interactive Graphics Engine

## 💻 Overview
A custom 2D rendering and animation project built from scratch using **C++**, **SDL3**, and **GLM**. This application demonstrates real-time vector-based movement, custom circle rasterization algorithms, and dynamic input handling. The project features a smooth "follow" mechanic where geometric shapes track the user's mouse cursor in real-time.

---

## 🤍 Tech Stack
* **Language:** C++
* **Libraries:** SDL3 (Graphics & Input), GLM (Mathematics)
* **Concepts:** 2D Rendering, Vector Math, Algorithmic Rasterization, Delta-Time Animation
* **Tools:** Visual Studio / VS Code, Git

![C++](https://img.shields.io/badge/C%2B%2B-Language-%23FF69B4.svg?style=for-the-badge&logo=cplusplus&logoColor=white) ![SDL3](https://img.shields.io/badge/SDL3-Graphics-%23FF69B4.svg?style=for-the-badge&logo=sdl&logoColor=white)

---

## 🎀 Core Functionality
* **Custom Shape Rendering:** Implements a manual rasterization algorithm to draw and fill circles, as native SDL3 does not provide direct circle-filling primitives.
* **Vector-Based Movement:** Utilizes `GLM` to calculate normalized direction vectors, ensuring smooth, frame-rate independent object tracking toward mouse coordinates.
* **Dynamic Input Handling:** Supports real-time user interaction, including mouse-motion tracking, left-click events, and keyboard-based manual control via arrow keys.
* **High-DPI Support:** Integrated display scaling logic ensures the application renders correctly across various monitor resolutions and pixel densities.

---

## 📂 Project Structure
* **`main.cpp`**: Orchestrates the main game loop, input processing, and rendering pipeline.
* **`circle.h / circle.cpp`**: Contains the definition and implementation of the `Circle` class and the custom rasterization algorithms.
* **`glm/`**: External library for linear algebra and vector operations.

---

© 2025 Graphics Engine | Developed by [**𝐋𝐞𝐨𝐧𝐭𝐞 𝐏𝐚𝐭𝐫𝐢𝐜𝐢𝐚-𝐌𝐢𝐫𝐚𝐛𝐞𝐥𝐚**](https://patrrrrrrricia.github.io/glowing-button/)
