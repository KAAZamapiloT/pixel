# 🎮 Pixel Renderer


A small software renderer built to understand how graphics actually work.

## 🔲 Cube Rendering Demo

<p align="center">
  <img src="assets/temp.gif" width="250"/>
</p>

---

## ✨ What it does

- 🎥 Free camera movement + rotation  
- 🔺 Renders triangles (2D + 3D)  
- 🧊 Renders Cube
- 🧠 Basic rendering pipeline (manual, no engine magic)

---

## 🎯 Why this exists

To learn:
- how 3D → 2D projection works  
- how cameras behave  
- how triangles become pixels  

---

## 🚧 Current limits

- No meshes  
- No lighting  
- No depth buffer  
- CPU only  

---

## ⚙️ Build

```bash
mkdir build
cd build
cmake ..
make
