#include <iostream>
#include "OCRTestApp.h"

using namespace PDLS;

int main(int argc, char** argv) {
    if(argc != 2) {
        std::cerr << "Wrong Call Syntax!" << std::endl;
        std::cerr << "Good Call Syntax: " << argv[0] << "/path/to/document" << std::endl;
    }

    OCRTestApp app;
    app.run(argv[1]);
    return 0;
}