# Multi-Threaded C++20 3D Ray Tracer

A high-performance, concurrent ray tracer built from scratch in modern C++20. Features custom vector mathematics, geometric ray-sphere intersections, and multi-threaded image rendering via asynchronous task distribution.

![C++ Standard](https://img.shields.io/badge/C%2B%2B-20-blue.svg)
![Build System](https://img.shields.io/badge/CMake-3.16%2B-brightgreen.svg)
![License](https://img.shields.io/badge/License-MIT-yellow.svg)

---

## 🌟 Key Features

* **Zero External Dependencies:** Implements custom 3D vector math, ray optics, and PPM image output natively without external graphics libraries.
* **Concurrent Multi-Threading:** Utilizes `std::future` and `std::async` to partition rendering workloads across all available hardware CPU threads.
* **Optimized Ray-Sphere Intersections:** Solves analytical quadratic equations for precise 3D surface collision detection.

---

## ⚙️ Building & Running

### Prerequisites
* CMake 3.16+
* C++20 Compliant Compiler (MSVC, GCC, or Clang)

### Build Steps
```bash
git clone [https://github.com/YOUR_USERNAME/cpp-multithreaded-raytracer.git](https://github.com/YOUR_USERNAME/cpp-multithreaded-raytracer.git)
cd cpp-multithreaded-raytracer
mkdir build && cd build
cmake ..
cmake --build . --config Release

# Run the Ray Tracer
./RayTracer
