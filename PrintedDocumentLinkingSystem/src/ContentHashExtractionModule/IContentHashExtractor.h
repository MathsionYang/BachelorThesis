#ifndef PRINTEDDOCUMENTVERIFICATIONSYSTEM_CONTENTHASHEXTRACTIONSTRATEGY_H
#define PRINTEDDOCUMENTVERIFICATIONSYSTEM_CONTENTHASHEXTRACTIONSTRATEGY_H

#include "../Datatypes/Document.h"
#include "../Datatypes/ContentHash.h"
#include "../Datatypes/EnumTypes.h"

namespace PDLS {

    class IContentHashExtractor {
    protected:
        ContentHashType _expectedHashType;

    public:
        IContentHashExtractor(const ContentHashType& hT) : _expectedHashType(hT) {}

        virtual ContentHash* extractContentHash(Document* doc, const std::string& hashPrefix, const std::string& hashPostfix) = 0;
        virtual ~IContentHashExtractor() {}

        ContentHashType getExpectedHashType() const {
            return _expectedHashType;
        }

        void setExpectedHashType(ContentHashType expectedHashType) {
            _expectedHashType = expectedHashType;
        }
    };

}

#endif //PRINTEDDOCUMENTVERIFICATIONSYSTEM_CONTENTHASHEXTRACTIONSTRATEGY_H
