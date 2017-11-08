#include "ImagePDFExtractor.h"
#include "../ContentExtractionModule.h"

namespace PDLS {

    Content* ImagePDFExtractor::extractContent(Document* pdfDoc) throw(PDLSException) {
        Document* imgDoc = _pdf2ImageConverter->convertPDF2Image(pdfDoc, _imageConversionDPI);
        Content* res = _imageExtractor->extractContent(imgDoc);

        //delete converted doc unless user wants to save it
        if(!ContentExtractionModule::getInstance()->saveConvertedDocument()) {
            imgDoc->removeFromDisk();
        }

        /* TODO VTable error?!
        if(!PrintedDocumentLinkingSystem::getInstance()->saveConvertedFile()) {
            imgDoc->removeFromDisk();
        }
        */

        return res;
    }

}
