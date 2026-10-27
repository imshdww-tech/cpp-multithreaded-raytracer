#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <future>
#include "Vector3.hpp"
#include "Ray.hpp"
#include "Sphere.hpp"

Vector3 rayColor(const Ray& r, const Sphere& sphere) {
    HitRecord rec = sphere.hit(r, 0.001, 1000.0);
    if (rec.hit) {
        Vector3 N = rec.normal;
        return 0.5 * Vector3(N.x + 1.0, N.y + 1.0, N.z + 1.0);
    }
    Vector3 unitDir = r.dir.normalize();
    auto t = 0.5 * (unitDir.y + 1.0);
    return (1.0 - t) * Vector3(1.0, 1.0, 1.0) + t * Vector3(0.5, 0.7, 1.0);
}

int main() {
    // Image Configuration
    const auto aspectRat = 16.0 / 9.0;
    const int imageWidth = 800;
    const int imageHeight = static_cast<int>(imageWidth / aspectRat);

    std::cout << "Rendering 3D Scene (" << imageWidth << "x" << imageHeight << ") using Multi-Threading...\n";

    // Camera Setup
    auto viewportHeight = 2.0;
    auto viewportWidth = aspectRat * viewportHeight;
    auto focalLength = 1.0;

    Vector3 origin(0, 0, 0);
    Vector3 horizontal(viewportWidth, 0, 0);
    Vector3 vertical(0, viewportHeight, 0);
    Vector3 lowerLeftCorner = origin - horizontal / 2 - vertical / 2 - Vector3(0, 0, focalLength);

    Sphere worldSphere(Vector3(0, 0, -1), 0.5);

    // Buffer for image
    std::vector<std::vector<Vector3>> framebuffer(imageHeight, std::vector<Vector3>(imageWidth));

    // Multi-threaded row processing
    auto renderRow = [&](int startY, int endY) {
        for (int j = startY; j < endY; ++j) {
            for (int i = 0; i < imageWidth; ++i) {
                double u = static_cast<double>(i) / (imageWidth - 1);
                double v = static_cast<double>(imageHeight - 1 - j) / (imageHeight - 1);
                Ray r(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);
                framebuffer[j][i] = rayColor(r, worldSphere);
            }
        }
    };

    // Split work across available CPU threads
    unsigned int numThreads = std::thread::hardware_concurrency();
    if (numThreads == 0) numThreads = 2;
    std::vector<std::future<void>> futures;
    int chunkHeight = imageHeight / numThreads;

    auto startTime = std::chrono::high_resolution_clock::now();

    for (unsigned int t = 0; t < numThreads; ++t) {
        int startY = t * chunkHeight;
        int endY = (t == numThreads - 1) ? imageHeight : (t + 1) * chunkHeight;
        futures.push_back(std::async(std::launch::async, renderRow, startY, endY));
    }

    for (auto& f : futures) {
        f.get();
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = endTime - startTime;
    std::cout << "Rendering completed in " << duration.count() << " ms across " << numThreads << " threads!\n";

    // Output to PPM Image File
    std::ofstream outFile("render.ppm");
    outFile << "P3\n" << imageWidth << " " << imageHeight << "\n255\n";
    for (int j = 0; j < imageHeight; ++j) {
        for (int i = 0; i < imageWidth; ++i) {
            int ir = static_cast<int>(255.999 * framebuffer[j][i].x);
            int ig = static_cast<int>(255.999 * framebuffer[j][i].y);
            int ib = static_cast<int>(255.999 * framebuffer[j][i].z);
            outFile << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }
    outFile.close();
    std::cout << "Image saved successfully as 'render.ppm'.\n";

    return 0;
}
