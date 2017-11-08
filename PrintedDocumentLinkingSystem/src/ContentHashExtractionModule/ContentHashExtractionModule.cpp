#include "ContentHashExtractionModule.h"
#include "../Datatypes/EnumTypes.h"

namespace PDLS {

    ContentHash* ContentHashExtractionModule::extractContentHash(Document* doc, ContentHashType hT, const std::string& hashPrefix, const std::string& hashPostfix) throw (PDLSException){
        if(_contentHashExtractionStrategy == nullptr)
            throw NoStrategyException("CHEM");

        _contentHashExtractionStrategy->setExpectedHashType(hT);
        ContentHash* extractedContentHash = nullptr;
        if(doc->getContentHash() != nullptr)
            extractedContentHash = doc->getContentHash();
        else
            extractedContentHash = _contentHashExtractionStrategy->extractContentHash(doc, hashPrefix, hashPostfix);

        return extractedContentHash;
    }

}
