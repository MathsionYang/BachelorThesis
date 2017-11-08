#include "TextPDFExtractor.h"
#include "../ContentExtractionModule.h"

namespace PDLS {

    Content* TextPDFExtractor::extractContent(Document* pdfDoc) throw(PDLSException) {
        Document* txtDoc = _pdf2TextConverter->convertPDF2Text(pdfDoc);
        Content* res = txtDoc->getContent();

        //delete converted doc unless user wants to save it
        if(!ContentExtractionModule::getInstance()->saveConvertedDocument()) {
            txtDoc->removeFromDisk();
        }

        /* TODO Vtable error?!
        if(!PrintedDocumentLinkingSystem::getInstance()->saveConvertedFile()) {
            txtDoc->removeFromDisk();
            delete txtDoc;
        }
        */

        return res;
    }

}
