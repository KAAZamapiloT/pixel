#pragma once

#include <SDL3/SDL.h>
#include <algorithm>

class Benchmark {
public:
    void Begin() {
        start = SDL_GetPerformanceCounter();
    }

    void End() {
        uint64_t end = SDL_GetPerformanceCounter();

        double t =
            1000.0 *
            static_cast<double>(end - start) /
            SDL_GetPerformanceFrequency();

        avg += (t - avg) / ++frames;
        min_latency = std::min(min_latency, t);
        max_latency = std::max(max_latency, t);
    }

    void Print() const {
        printf(
            "Frames: %llu | "
            "Avg: %.3f ms | "
            "Min: %.3f ms | "
            "Max: %.3f ms\n",
            frames,
            avg,
            min_latency,
            max_latency
        );
    }

private:
    uint64_t start = 0;
    uint64_t frames = 0;

    double avg = 0.0;
    double min_latency = std::numeric_limits<double>::max();
    double max_latency = 0.0;
};
