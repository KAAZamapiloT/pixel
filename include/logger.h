#pragma once
#include <iostream>
#include <chrono>

namespace Pixel {

enum class LogLevel {
    Debug = 0,
    Info,
    Warning,
    Error
};

class PixelLogger {
public:
    // ===== LOG LEVEL =====
    static LogLevel level;

    // ===== CORE LOG =====
    static void Log(LogLevel lvl, const char* msg,
                    const char* file, int line)
    {
        if (lvl < level) return;

        std::cout << "[" << ToString(lvl) << "] "
                  << "[" << file << ":" << line << "] "
                  << msg << "\n";
    }

    // ===== FPS =====
    static void UpdateFPS() {
        using namespace std::chrono;

        auto now = high_resolution_clock::now();
        frameCount++;

        float delta = duration<float>(now - lastTime).count();
        if (delta >= 1.0f) {
            fps = frameCount;
            frameCount = 0;
            lastTime = now;
        }
    }

    static int GetFPS() { return fps; }

private:
    static const char* ToString(LogLevel lvl) {
        switch (lvl) {
            case LogLevel::Debug: return "D";
            case LogLevel::Info: return "I";
            case LogLevel::Warning: return "W";
            case LogLevel::Error: return "E";
        }
        return "";
    }

private:
    inline static int fps = 0;
    inline static int frameCount = 0;
    inline static std::chrono::high_resolution_clock::time_point lastTime =
        std::chrono::high_resolution_clock::now();
};

// default level
inline LogLevel PixelLogger::level = LogLevel::Debug;

} // namespace Pixel

// ===== MACROS =====
#define PLOG(lvl, msg) Pixel::PixelLogger::Log(lvl, msg, __FILE__, __LINE__)

#define PDEBUG(msg) PLOG(Pixel::LogLevel::Debug, msg)
#define PINFO(msg)  PLOG(Pixel::LogLevel::Info, msg)
#define PWARN(msg)  PLOG(Pixel::LogLevel::Warning, msg)
#define PERROR(msg) PLOG(Pixel::LogLevel::Error, msg)

// renderer
#define PRENDER(msg) PDEBUG("[Renderer] " msg)

// fps
#define PFPS() PDEBUG("[FPS]")
