#include "LinkExtractionModule.h"

namespace PDLS {

    Link* LinkExtractionModule::extractLink(Document* doc, LinkDescription* desc) throw(PDLSException) {
        if(!doc || !desc)
            throw NullPointerException("LDataLinkExtractionModule::extractLink");

        switch(doc->getType()) {
            case FileType::IMG:
            case FileType::PDF:
                if(_extractQRCodeLink)
                    return _qrCodeLinkExtractor->extractLink(doc, desc);
                else
                    return _textLinkExtractor->extractLink(doc, desc);
            case FileType::TXT:
            case FileType::XML:
                return _textLinkExtractor->extractLink(doc, desc);
            case FileType::CRYPTO:
                throw NoStrategyException("LinkExtractionModule");
        }

    }
}

