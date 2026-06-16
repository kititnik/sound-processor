#pragma once

#include <string_view>
#include <memory>

class ILogger {
public:
    virtual void log(std::string_view msg) = 0;
    virtual ~ILogger() = default;
};

class NullLogger : public ILogger {
public:
    void log(std::string_view) override {}
};

class Logger {
public:
    static void set(std::shared_ptr<ILogger> logger);
    static void log(std::string_view msg);
private:
    static std::shared_ptr<ILogger> _logger;
};