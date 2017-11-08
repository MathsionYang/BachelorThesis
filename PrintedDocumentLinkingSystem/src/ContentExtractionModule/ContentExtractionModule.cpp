#include "ContentExtractionModule.h"

#include "ImageExtraction/OCRExtractor.h"
#include "PDFExtraction/TextPDFExtractor.h"
#include "PDFExtraction/ImagePDFExtractor.h"
#include "XMLExtraction/XMLExtractor.h"
//#include "../PrintedDocumentLinkingSystem.h"

namespace PDLS {

    Content* ContentExtractionModule::extractContent(Document* doc) throw(PDLSException) {
        switch (doc->getType()) {
            case FileType::IMG:
                return _imageExtractionStrategy->extractContent(doc);
            case FileType::TXT:
                return doc->getContent();
            case FileType::XML:
                return  _xmlExtractionStrategy->extractContent(doc);
            case FileType::PDF:
                if(/*PrintedDocumentLinkingSystem::getInstance()->inputIsTextPDF()*/_inputTreatedAsTextPDF) //VTable Error?!
                    return _textPDFExtractionStrategy->extractContent(doc);
                else
                    return _imagePDFExtractionStrategy->extractContent(doc);

            case FileType::CRYPTO:break;
        }
    }

    void ContentExtractionModule::createDefaultStrategies() {
        _imageExtractionStrategy = new OCRExtractor();
        _textPDFExtractionStrategy = new TextPDFExtractor();
        _imagePDFExtractionStrategy= new ImagePDFExtractor();
        _xmlExtractionStrategy = new XMLExtractor("//fo:inline");
    }

}
