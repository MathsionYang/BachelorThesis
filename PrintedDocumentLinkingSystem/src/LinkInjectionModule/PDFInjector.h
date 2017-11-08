#ifndef PRINTEDDOCUMENTLINKINGSYSTEM_PDFINJECTOR_H
#define PRINTEDDOCUMENTLINKINGSYSTEM_PDFINJECTOR_H

#include "ILinkInjector.h"
#include "../Util/IImage2PDFConverter.h"
#include "../Util/IPDF2ImageConverter.h"
#include "../Util/SimplePythonImage2PDFConverter.h"
#include "../Util/GhostScriptPDFManipulator.h"
#include "ImageInjector.h"

namespace PDLS {

    class PDFInjector : public ILinkInjector {

        IPDF2ImageConverter* _pdf2imgConverter;
        IImage2PDFConverter* _img2pdfConverter;
        ImageInjector* _imgInjector;

    public:
        PDFInjector() : _pdf2imgConverter(GhostScriptPDFManipulator::getInstance()),
                        _img2pdfConverter(SimplePythonImage2PDFConverter::getInstance()),
                        _imgInjector(new ImageInjector()) {} //TODO make every non-datatype class a singleton..

        virtual void injectLink(Document* pdfDoc, Link* l, const bfs::path& out) throw (PDLSException) override;
    };
}


#endif //PRINTEDDOCUMENTLINKINGSYSTEM_PDFINJECTOR_H
