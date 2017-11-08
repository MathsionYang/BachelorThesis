#include <iostream>
#include "PrintedDocumentLinkingSystem.h"

using namespace PDLS;

int main(int argc, char** argv) {
    PrintedDocumentLinkingSystem* pdvs = PrintedDocumentLinkingSystem::getInstance();
    pdvs->run(argc, argv);
    return 0;
}