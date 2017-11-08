#include "PDFInjector.h"
#include "LinkInjectionModule.h"

namespace PDLS {
    
    void PDFInjector::injectLink(Document* pdfDoc, Link* l, const bfs::path& out) throw(PDLSException) {
        if(pdfDoc == nullptr || link == nullptr)
            throw NullPointerException("PDFInjector::injectLink");
        if(pdfDoc->getType() != FileType::PDF)
            throw StrategyMismatchException("PDFInjector::injectLink");

        //convert pdf to img
        Document* imgDoc = _pdf2imgConverter->convertPDF2Image(pdfDoc, 300);

        //inject link into img

        //set a temporary new name with extension png because openCV throws an error if extension is non image format
        bfs::path tmpOut(std::string(out.string() + ".png").c_str());
        _imgInjector->injectLink(imgDoc, l, tmpOut);

        //create new document from linked image document
        Document* linkedImgDoc = new Document(tmpOut);

        //convert img back to pdf
        Document* linkedPDFDoc = _img2pdfConverter->convertImage2PDF(linkedImgDoc);

        //rename linkedPDFDoc to out
        linkedPDFDoc->rename(out);

        //delete the converted files if user doesnt want to save it
        if(!LinkInjectionModule::getInstance()->isSaveConvertedDocument()){
            imgDoc->removeFromDisk();
            linkedImgDoc->removeFromDisk();
        }

        /* TODO VTable Error?!
        if(!PrintedDocumentLinkingSystem::getInstance()->saveConvertedFile()){
            imgDoc->removeFromDisk();
            linkedImgDoc->removeFromDisk();
        }
         */
    }
    
}
