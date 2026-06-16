#pragma once

#include "logger.hpp"

class ConsoleLogger : public ILogger {
public:
    void log(std::string_view msg) override;
};
