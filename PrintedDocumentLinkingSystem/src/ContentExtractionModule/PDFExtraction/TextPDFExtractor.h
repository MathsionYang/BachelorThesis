#ifndef CONTENTEXTRACTIONMODULE_TEXTPDFEXTRACTOR_H
#define CONTENTEXTRACTIONMODULE_TEXTPDFEXTRACTOR_H

#include "../IExtractionStrategy.h"
#include "../../Util/IPDF2TextConverter.h"
#include "../../Util/GhostScriptPDFManipulator.h"

namespace PDLS {

    class TextPDFExtractor : public IExtractionStrategy {
        IPDF2TextConverter* _pdf2TextConverter;
    public:
        virtual Content* extractContent(Document* doc) throw(PDLSException) override;

        TextPDFExtractor() : _pdf2TextConverter(GhostScriptPDFManipulator::getInstance()) {}
    };

}

#endif //CONTENTEXTRACTIONMODULE_TEXTPDFEXTRACTOR_H
