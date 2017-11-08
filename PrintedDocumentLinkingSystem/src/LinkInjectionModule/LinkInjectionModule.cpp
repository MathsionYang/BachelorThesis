#include "LinkInjectionModule.h"

#include "../Datatypes/EnumTypes.h"
#include "../Datatypes/Link.h"

namespace PDLS {

    void LinkInjectionModule::injectLink(Document* doc, Link* link, const bfs::path& out) throw(PDLSException) {
        if(doc == nullptr || link == nullptr)
            throw NullPointerException("LinkInjectionModule::injectLink");

        switch (doc->getType()) {
            case FileType::XML:
                if(!_xmlInjectionstrategy)
                    throw NoStrategyException("LDataLIM");
                _xmlInjectionstrategy->injectLink(doc, link, out);
                break;
            case FileType::IMG:
                if(!_imageInjectionstrategy)
                    throw NoStrategyException("LDataLIM");
                _imageInjectionstrategy->injectLink(doc, link, out);
                break;
            case FileType::TXT:
                if(!_textInjectionstrategy)
                    throw NoStrategyException("LDataLIM");
                _textInjectionstrategy->injectLink(doc, link, out);
                break;
            case FileType::PDF:
                if(!_pdfInjectionstrategy)
                    throw NoStrategyException("LDataLIM");
                _pdfInjectionstrategy->injectLink(doc, link, out);
                break;
            case FileType::CRYPTO:
                throw NoStrategyException("LDataLIM");
        }
    }
}

