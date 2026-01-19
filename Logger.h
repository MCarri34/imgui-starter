#pragma once
#include <fstream>
#include <string>
#include <vector>

enum class LogLevel
{
    Info = 0,
    Warning = 1,
    Error = 2
};

class Logger
{
public:
    struct LogEntry
    {
        LogLevel level;
        std::string text;
    };

    static Logger& GetInstance()
    {
        static Logger instance;
        return instance;
    }

    void Initialize(const char* filename = "GameLog.txt")
    {
        logFilename = filename ? filename : "GameLog.txt";
        initialized = true;
        // Do NOT open the file here. We'll open lazily on first Log().
    }

    void Log(LogLevel level, const std::string& message)
    {
        const char* prefix =
            level == LogLevel::Info    ? "[INFO] " :
            level == LogLevel::Warning ? "[WARN] " :
                                         "[ERROR] ";

        std::string full = std::string(prefix) + message;

        // Always store for the on-screen console
        entries.push_back({ level, full });

        // Lazy-open file the first time we log (safe in early startup)
        if (!file.is_open())
        {
            if (!initialized)
                logFilename = "GameLog.txt";

            file.open(logFilename, std::ios::out | std::ios::app);
        }

        if (file.is_open())
        {
            file << full << "\n";
            file.flush();
        }
    }

    void Clear()
    {
        entries.clear();
    }

    void SetConsoleLevel(LogLevel level)
    {
        consoleLevel = level;
    }

    LogLevel GetConsoleLevel() const
    {
        return consoleLevel;
    }

    const std::vector<LogEntry>& GetEntries() const
    {
        return entries;
    }

private:
    Logger() = default;
    ~Logger()
    {
        if (file.is_open())
            file.close();
    }

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

private:
    std::ofstream file;
    const char* logFilename = "GameLog.txt";
    bool initialized = false;

    std::vector<LogEntry> entries;
    LogLevel consoleLevel = LogLevel::Info;
};
