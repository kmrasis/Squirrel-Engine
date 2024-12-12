#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#ifdef SQ_ENABLE_TRACE_LOGGING
#include <spdlog/sinks/rotating_file_sink.h>
#endif

/**
 * Logging Macros :: For quick logging to console (Can log to file also if needed)
 */

#ifdef SQ_ENABLE_TRACE_LOGGING

// Log message Marcos  :: For debugging purposes
#define LOG_TRACE(...)                                                                                                 \
  if (nullptr != ::Utils::Logger::GetCoreLogger())                                                                     \
  {                                                                                                                    \
    ::Utils::Logger::GetCoreLogger()->log(                                                                             \
        spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::trace, __VA_ARGS__);                   \
  }

#define LOG_DEBUG(...)                                                                                                 \
  if (nullptr != ::Utils::Logger::GetCoreLogger())                                                                     \
  {                                                                                                                    \
    ::Utils::Logger::GetCoreLogger()->log(                                                                             \
        spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::debug, __VA_ARGS__);                   \
  }

#define LOG_INFO(...)                                                                                                  \
  if (nullptr != ::Utils::Logger::GetCoreLogger())                                                                     \
  {                                                                                                                    \
    ::Utils::Logger::GetCoreLogger()->log(                                                                             \
        spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::info, __VA_ARGS__);                    \
  }

#define LOG_WARN(...)                                                                                                  \
  if (nullptr != ::Utils::Logger::GetCoreLogger())                                                                     \
  {                                                                                                                    \
    ::Utils::Logger::GetCoreLogger()->log(                                                                             \
        spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::warn, __VA_ARGS__);                    \
  }

#define LOG_ERROR(...)                                                                                                 \
  if (nullptr != ::Utils::Logger::GetCoreLogger())                                                                     \
  {                                                                                                                    \
    ::Utils::Logger::GetCoreLogger()->log(                                                                             \
        spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::err, __VA_ARGS__);                     \
  }

#define CONSOLE_INFO(...)                                                                                              \
  if (nullptr != ::Utils::Logger::GetConsoleLogger())                                                                  \
  {                                                                                                                    \
    ::Utils::Logger::GetConsoleLogger()->info(__VA_ARGS__);                                                            \
  }                                                                                                                    \
  LOG_INFO(__VA_ARGS__)

#define CONSOLE_WARN(...)                                                                                              \
  if (nullptr != ::Utils::Logger::GetConsoleLogger())                                                                  \
  {                                                                                                                    \
    ::Utils::Logger::GetConsoleLogger()->warn(__VA_ARGS__);                                                            \
  }                                                                                                                    \
  LOG_WARN(__VA_ARGS__)

#define CONSOLE_ERROR(...)                                                                                             \
  if (nullptr != ::Utils::Logger::GetConsoleLogger())                                                                  \
  {                                                                                                                    \
    ::Utils::Logger::GetConsoleLogger()->error(__VA_ARGS__);                                                           \
  }                                                                                                                    \
  LOG_ERROR(__VA_ARGS__)

#else
#define CONSOLE_INFO(...)                                                                                              \
  if (nullptr != ::Utils::Logger::GetConsoleLogger())                                                                  \
  {                                                                                                                    \
    ::Utils::Logger::GetConsoleLogger()->info(__VA_ARGS__);                                                            \
  }

#define CONSOLE_WARN(...)                                                                                              \
  if (nullptr != ::Utils::Logger::GetConsoleLogger())                                                                  \
  {                                                                                                                    \
    ::Utils::Logger::GetConsoleLogger()->warn(__VA_ARGS__);                                                            \
  }

#define CONSOLE_ERROR(...)                                                                                             \
  if (nullptr != ::Utils::Logger::GetConsoleLogger())                                                                  \
  {                                                                                                                    \
    ::Utils::Logger::GetConsoleLogger()->error(__VA_ARGS__);                                                           \
  }

#endif

namespace Utils
{
/**
 * Using dual logger object approach:
 *  1. For printing colored output to console
 *      PATTERN : [date and time] [log level] [log message]
 *      EXAMPLE : [2024-11-30 13:07:48.767] [error] Example error log message.
 *
 *  2. For logging to file for debugging and/or testing purposes
 *      PATTERN : [date and time] [pid] [log level] [function] in [file name:line number] [log message]
 *      EXAMPLE : [2024-11-30 13:07:48.767] [18475] [error] run() in application.cpp:24 Example
 *                error log message
 */

class Logger
{
public:
  static void Init()
  {
#ifdef SQ_ENABLE_TRACE_LOGGING
    // Use rotating file sink for debug logs
    core_logger_ = spdlog::rotating_logger_mt("core_logger", "logs/output.log", 1048576 * 100, 3);
    core_logger_->set_level(spdlog::level::trace);
    core_logger_->flush_on(spdlog::level::info);
    core_logger_->set_pattern("[%Y-%m-%d %X.%e] [%P] [%l] %!() in %s:%# %v");
#endif
    // Use color coding for console output
    console_logger_ = spdlog::stdout_color_mt("CONSOLE");
    console_logger_->set_pattern("%^[%Y-%m-%d %X.%e] [%l] %v%$");
    CONSOLE_INFO("Initialised Logger successfully");
  }

  static void DeInit()
  {
    CONSOLE_INFO("DeInitialising Logger");

#ifdef SQ_ENABLE_TRACE_LOGGING
    core_logger_->flush();
#endif
    console_logger_->flush();
    spdlog::shutdown();
  }

#ifdef SQ_ENABLE_TRACE_LOGGING
  inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return core_logger_; }
#endif
  inline static std::shared_ptr<spdlog::logger>& GetConsoleLogger() { return console_logger_; }

private:
#ifdef SQ_ENABLE_TRACE_LOGGING
  inline static std::shared_ptr<spdlog::logger> core_logger_;
#endif
  inline static std::shared_ptr<spdlog::logger> console_logger_;
};
} // namespace Utils
