#ifndef PRINTEDDOCUMENTLINKINGSYSTEM_OCRTESTAPP_H
#define PRINTEDDOCUMENTLINKINGSYSTEM_OCRTESTAPP_H

#include "ContentExtractionModule/ContentExtractionModule.h"
#include "ContentNormalizationModule/ContentNormalizationModule.h"

using namespace PDLS;

struct OCRTestApp {
    ContentExtractionModule* _cem;
    ContentNormalizationModule* _csm;

    OCRTestApp() : _cem(ContentExtractionModule::getInstance()), _csm(ContentNormalizationModule::getInstance()) {}
    void run(const std::string& pathToDoc);
};



#endif //PRINTEDDOCUMENTLINKINGSYSTEM_OCRTESTAPP_H
