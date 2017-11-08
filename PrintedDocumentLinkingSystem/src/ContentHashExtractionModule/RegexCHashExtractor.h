#ifndef PRINTEDDOCUMENTVERIFICATIONSYSTEM_REGEXCHASHEXTRACTOR_H
#define PRINTEDDOCUMENTVERIFICATIONSYSTEM_REGEXCHASHEXTRACTOR_H

#include <map>
#include "IContentHashExtractor.h"
#include "../Datatypes/ContentHash.h"
#include "../Datatypes/Document.h"

namespace PDLS {

    class RegexCHashExtractor : public IContentHashExtractor {

        std::map<ContentHashType, const std::string*> _contentHashMatcherMap {};

        Content* extractDocumentContent(Document* pDocument);

        void generateContentHashMatcherMap();
    public:

        RegexCHashExtractor(const ContentHashType& hT);

        virtual ContentHash* extractContentHash(Document* doc, const std::string& hashPrefix, const std::string& hashPostfix) override;

        inline const std::string* getContentHashMatcher(const ContentHashType& hT) {
            return _contentHashMatcherMap[hT];
        }

        inline const std::string* getContentHashMatcher() {
            return _contentHashMatcherMap[_expectedHashType];
        }

    };

}

#endif //PRINTEDDOCUMENTVERIFICATIONSYSTEM_REGEXCHASHEXTRACTOR_H
