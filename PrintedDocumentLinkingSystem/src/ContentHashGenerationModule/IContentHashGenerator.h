#ifndef PRINTEDDOCUMENTLINKINGSYSTEM_ICONTENTHASHGENERATOR_H
#define PRINTEDDOCUMENTLINKINGSYSTEM_ICONTENTHASHGENERATOR_H

#include "../Datatypes/NormalizedContent.h"
#include "../Datatypes/ContentHash.h"

namespace PDLS {
    struct IContentHashGenerator {
        virtual ContentHash* generateContentHash(NormalizedContent* sdc) throw(PDLSException) = 0;
        virtual ~IContentHashGenerator() {};
    };
}

#endif //PRINTEDDOCUMENTLINKINGSYSTEM_ICONTENTHASHGENERATOR_H
