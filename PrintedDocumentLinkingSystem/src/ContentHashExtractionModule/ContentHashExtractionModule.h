#ifndef PRINTEDDOCUMENTVERIFICATIONSYSTEM_CONTENTHASHEXTRACTIONMODULE_H
#define PRINTEDDOCUMENTVERIFICATIONSYSTEM_CONTENTHASHEXTRACTIONMODULE_H

#include "IContentHashExtractor.h"
#include "RegexCHashExtractor.h"
#include "../Datatypes/ContentHash.h"
#include "../Datatypes/Document.h"
#include "../Datatypes/PDLSException.h"
#include "../Datatypes/EnumTypes.h"

namespace PDLS {

    class ContentHashExtractionModule {

        IContentHashExtractor* _contentHashExtractionStrategy;

        ContentHashExtractionModule() : _contentHashExtractionStrategy(nullptr) { createDefaultStrategy(); }

    public:

        static ContentHashExtractionModule* getInstance() {
            static ContentHashExtractionModule singleton;
            return &singleton;
        }

        ContentHash* extractContentHash(Document* inDoc, ContentHashType hT, const std::string& hashPrefix, const std::string& hashPostfix) throw (PDLSException);

        IContentHashExtractor* getCHashExtractionStrategy() const {
            return _contentHashExtractionStrategy;
        }

        void setCHashExtractionStrategy(IContentHashExtractor* cHashExtractionStrategy) {
            _contentHashExtractionStrategy = cHashExtractionStrategy;
        }

        void createDefaultStrategy() {
            _contentHashExtractionStrategy = new RegexCHashExtractor(ContentHashType::SHA256);
        }

        ContentHashExtractionModule(const ContentHashExtractionModule&) = delete;
        void operator=(const ContentHashExtractionModule&) = delete;
    };

}

#endif //PRINTEDDOCUMENTVERIFICATIONSYSTEM_CONTENTHASHEXTRACTIONMODULE_H
