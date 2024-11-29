#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>

/*
    Using dual logger object approach:
        1. For printing colored output to console
            PATTERN : [date and time] [log level] [log message]
            EXAMPLE : [2024-11-30 13:07:48.767] [error] Example error log message.
        
        2. For logging to file for debugging and/or testing purposes
            PATTERN : [date and time] [pid] [log level] [function] in [file name:line number] [log message]
            EXAMPLE : [2024-11-30 13:07:48.767] [18475] [error] run() in application.cpp:24 Example error log message
*/

namespace Log {
class Logger {
public:

    static void Init() {
        // Use rotating file sink for debug logs
        core_logger_ = spdlog::rotating_logger_mt("core_logger", "logs/output.log", 1048576 * 5, 3);
        core_logger_->set_level(spdlog::level::trace);
        core_logger_->flush_on(spdlog::level::info);
        core_logger_->set_pattern("[%Y-%m-%d %X.%e] [%P] [%l] %!() in %s:%# %v");

        // Use color coding for console output
        console_logger_ = spdlog::stdout_color_mt("CONSOLE");
        console_logger_->set_pattern("%^[%Y-%m-%d %X.%e] [%l] %v%$");

    }

    inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() {return core_logger_;}
    inline static std::shared_ptr<spdlog::logger>& GetConsoleLogger() {return console_logger_;}

private:
    inline static std::shared_ptr<spdlog::logger> core_logger_;
    inline static std::shared_ptr<spdlog::logger> console_logger_;
};
} // namespace Log

// SPDLOG SPECIFIC MACRSO/FLAGS
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE

// Console Output Marcos :: For Printing to console  
#define CONSOLE_INFO(...) ::Log::Logger::GetConsoleLogger()->info(__VA_ARGS__); ::Log::Logger::GetCoreLogger()->log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::info, __VA_ARGS__)
#define CONSOLE_WARN(...) ::Log::Logger::GetConsoleLogger()->warn(__VA_ARGS__); ::Log::Logger::GetCoreLogger()->log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::warn, __VA_ARGS__)
#define CONSOLE_ERROR(...) ::Log::Logger::GetConsoleLogger()->error(__VA_ARGS__); ::Log::Logger::GetCoreLogger()->log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::err, __VA_ARGS__)

// Log message Marcos  :: For debugging purposes
#define LOG_TRACE(...) ::Log::Logger::GetCoreLogger()->log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::trace, __VA_ARGS__)
#define LOG_DEBUG(...) ::Log::Logger::GetCoreLogger()->log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::debug, __VA_ARGS__)
#define LOG_INFO(...) ::Log::Logger::GetCoreLogger()->log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::info, __VA_ARGS__)
#define LOG_WARN(...) ::Log::Logger::GetCoreLogger()->log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::warn, __VA_ARGS__)
#define LOG_ERROR(...) ::Log::Logger::GetCoreLogger()->log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::err, __VA_ARGS__)
