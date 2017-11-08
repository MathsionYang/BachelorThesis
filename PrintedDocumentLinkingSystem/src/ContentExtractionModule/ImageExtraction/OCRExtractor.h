#ifndef CONTENTEXTRACTIONMODULE_TESSERACTOCR_H
#define CONTENTEXTRACTIONMODULE_TESSERACTOCR_H

#include "../../Datatypes/Content.h"

#include "../IExtractionStrategy.h"

#include <tesseract/baseapi.h>
#include <opencv2/opencv.hpp>

namespace PDLS {

    class OCRExtractor : public IExtractionStrategy {

        std::string _ocrLanguage;
        tesseract::OcrEngineMode _ocrEngineMode;
        tesseract::PageSegMode _pageSegmentationMode;

        tesseract::TessBaseAPI* _tesseractAPI;

        void initTesseract();

    public:
        OCRExtractor() : _ocrLanguage("deu"),
                               _ocrEngineMode(tesseract::OcrEngineMode::OEM_DEFAULT),
                               _pageSegmentationMode(tesseract::PageSegMode::PSM_AUTO) { initTesseract(); }

        OCRExtractor(std::string& lang, tesseract::OcrEngineMode oem, tesseract::PageSegMode psm) :  _ocrLanguage(lang),
                                                                                                           _ocrEngineMode(oem),
                                                                                                           _pageSegmentationMode(psm) { initTesseract(); }

        virtual Content* extractContent(Document* doc) throw(PDLSException) override;
    };

}

#endif //CONTENTEXTRACTIONMODULE_TESSERACTOCR_H
