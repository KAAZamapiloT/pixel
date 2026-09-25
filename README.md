# 🎮 Pixel Renderer


A small software renderer built to understand how graphics actually work.

## 🔲 Cube Rendering Demo

<p align="center">
  <img src="assets/temp.gif" width="40%"/>
  <img src="assets/Cubes4.gif" width="40%"/>
</p>

---

## 🔵 Sphere Rendering Demo

<p align="center">
  <img src="assets/sphere.gif" width="40%"/>
  <img src="assets/Sphere2.gif" width="43%"/>
</p>

<p align="center">
  <sub>Left: Low resolution sphere | Right: Higher resolution / improved shading</sub>
</p>
## ✨ What it does

- 🎥 Free camera movement + rotation  
- 🔺 Renders triangles (2D + 3D)  
- 🧊 Renders Cube
- 🔵 Sphere rendering  
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
## Renderer Benchmark

### Scene
- Entities: 216
- Resolution: 512 × 512
- Camera: Perspective, 60° FOV
- Culling: Frustum + Back-face
- Animation: Continuous orbital rotation

### Current Baseline

| Metric | Result |
|---|---:|
| Frames | 779 |
| Average Frame Latency | **73.415 ms** |
| Minimum Latency | **0.384 ms** |
| Maximum Latency | **2712.139 ms** |
| Total Triangles | **2,019,168** |
| Drawn Triangles | **222,757** |
| Frustum Culls | **84,220** |
| Back-face Culls | **245,890** |

> Benchmark measures the `RenderMesh()` calls only. SDL texture upload and presentation are outside the measured region.

---

## ⚙️ Build

```bash
mkdir build
cd build
cmake ..
make
