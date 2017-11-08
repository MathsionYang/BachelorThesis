#ifndef CONTENTEXTRACTIONMODULE_XSLFOEXTRACTOR_H
#define CONTENTEXTRACTIONMODULE_XSLFOEXTRACTOR_H

#include "../IExtractionStrategy.h"
#include "../../Datatypes/Content.h"

namespace PDLS {

    class XMLExtractor : public IExtractionStrategy {

        std::string _contentElementNodeXPath;

    public:
        virtual Content* extractContent(Document* doc) throw(PDLSException) override;

        XMLExtractor(const std::string& xPath) : _contentElementNodeXPath(xPath) {}

        const std::string& getContentNodeXPath() const {
            return _contentElementNodeXPath;
        }

        void setContentNodeXPath(const std::string& contentNodeXPath) {
            _contentElementNodeXPath = contentNodeXPath;
        }
    };

}

#endif //CONTENTEXTRACTIONMODULE_XSLFOEXTRACTOR_H
