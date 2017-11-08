#ifndef CONTENTEXTRACTIONMODULE_IMAGEPDFEXTRACTOR_H
#define CONTENTEXTRACTIONMODULE_IMAGEPDFEXTRACTOR_H

#include "../../Datatypes/Document.h"
#include "../IExtractionStrategy.h"
#include "../ImageExtraction/OCRExtractor.h"
#include "../../Util/IPDF2ImageConverter.h"
#include "../../Util/GhostScriptPDFManipulator.h"

namespace PDLS {

    class ImagePDFExtractor : public IExtractionStrategy {
    private:

        OCRExtractor* _imageExtractor;
        IPDF2ImageConverter* _pdf2ImageConverter;
        int _imageConversionDPI;

    public:

        ImagePDFExtractor() : _imageExtractor(new OCRExtractor()),
                              _pdf2ImageConverter(GhostScriptPDFManipulator::getInstance()), _imageConversionDPI(600) {}

        ImagePDFExtractor(int dpi) : _imageExtractor(new OCRExtractor()),
                              _pdf2ImageConverter(GhostScriptPDFManipulator::getInstance()), _imageConversionDPI(dpi) {}

        virtual Content* extractContent(Document* doc) throw(PDLSException) override;

        OCRExtractor* getImageExtractor() const {
            return _imageExtractor;
        }

        void setImageExtractor(OCRExtractor* imageExtractor) {
            _imageExtractor = imageExtractor;
        }

    };

}

#endif //CONTENTEXTRACTIONMODULE_IMAGEPDFEXTRACTOR_H
