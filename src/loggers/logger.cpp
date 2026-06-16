#include "loggers/logger.hpp"
#include <memory>

std::shared_ptr<ILogger> Logger::_logger = std::make_shared<NullLogger>();

void Logger::set(std::shared_ptr<ILogger> logger) {
    _logger = std::move(logger);
}

void Logger::log(std::string_view msg) {
    _logger->log(msg);
}
