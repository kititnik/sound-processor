#include "application.hpp"
#include <cstdlib>
#include <iostream>

int main(int argc, char* argv[]) {
    Application app;
    try {
        app.configure();
        app.run(argc, argv);
    }
    catch(std::exception& exception) {
        std::cerr << "An exception handled: " << exception.what() << '\n';
        return EXIT_FAILURE;
    }
    catch(...) {
        std::cerr << "An unknown exception\n";
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
