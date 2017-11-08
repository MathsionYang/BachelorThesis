#ifndef PRINTEDDOCUMENTLINKINGSYSTEM_IIMAGE2PDFCONVERTER_H
#define PRINTEDDOCUMENTLINKINGSYSTEM_IIMAGE2PDFCONVERTER_H

#include "../Datatypes/Document.h"

namespace PDLS {

    struct IImage2PDFConverter {
        virtual ~IImage2PDFConverter() {}
        virtual Document* convertImage2PDF(Document* imgDoc) throw(PDLSException) = 0;
    };

}

#endif //PRINTEDDOCUMENTLINKINGSYSTEM_IIMAGE2PDFCONVERTER_H
