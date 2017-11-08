#ifndef PRINTEDDOCUMENTLINKINGSYSTEM_QRCODELINKEXTRACTOR_H
#define PRINTEDDOCUMENTLINKINGSYSTEM_QRCODELINKEXTRACTOR_H

#include "ILinkExtractor.h"
#include "../Util/IPDF2ImageConverter.h"
#include "../Util/GhostScriptPDFManipulator.h"

namespace PDLS {

    class QRCodeLinkExtractor : public ILinkExtractor {
        IPDF2ImageConverter* _pdf2imgConverter;
    public:
        QRCodeLinkExtractor() : _pdf2imgConverter(GhostScriptPDFManipulator::getInstance()) {}
        virtual Link* extractLink(Document* doc, LinkDescription* desc) throw(PDLSException) override;
    };

}
#endif //PRINTEDDOCUMENTLINKINGSYSTEM_QRCODELINKEXTRACTOR_H
