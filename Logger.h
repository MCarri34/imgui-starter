#pragma once
#include <fstream>
#include <string>
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"

enum class LogLevel
{
    Info,
    Warning,
    Error
};

class Logger
{
public:
    static Logger& GetInstance()
    {
        static Logger instance;
        return instance;
    }

    void Initialize()
    {
        if (!file.is_open())
            file.open("GameLog.txt");
    }

    void Log(LogLevel level, const std::string& message)
    {
        const char* prefix =
            level == LogLevel::Info    ? "[INFO] " :
            level == LogLevel::Warning ? "[WARN] " :
                                         "[ERROR] ";

        std::string full = std::string(prefix) + message + "\n";

        // Store for ImGui display
        logBuffer += full;

        // File output
        if (file.is_open())
            file << full;
    }

    const std::string& GetBuffer() const
    {
        return logBuffer;
    }

    void Clear()
    {
        logBuffer.clear();
    }

private:
    Logger() = default;
    ~Logger()
    {
        if (file.is_open())
            file.close();
    }

    std::ofstream file;
    std::string logBuffer;
};
