#include "loggers/console_logger.hpp"
#include <iostream>

void ConsoleLogger::log(std::string_view msg) {
    std::cout << msg << "\n";
}
