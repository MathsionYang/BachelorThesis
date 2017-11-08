#ifndef CONTENTEXTRACTIONMODULE_EXTRACTIONSTRATEGY_H
#define CONTENTEXTRACTIONMODULE_EXTRACTIONSTRATEGY_H

#include "../Datatypes/Document.h"

namespace PDLS {

    class IExtractionStrategy {
    public:
        virtual ~IExtractionStrategy() {}
        virtual Content* extractContent(Document* doc)  throw (PDLSException) = 0;
    };

}

#endif //CONTENTEXTRACTIONMODULE_EXTRACTIONSTRATEGY_H
