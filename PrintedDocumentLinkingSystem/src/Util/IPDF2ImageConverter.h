#ifndef CONTENTEXTRACTIONMODULE_PDF2IMGCONVERSIONINTERFACE_H
#define CONTENTEXTRACTIONMODULE_PDF2IMGCONVERSIONINTERFACE_H

#include "../Datatypes/Document.h"

namespace PDLS {

    struct IPDF2ImageConverter {
        virtual ~IPDF2ImageConverter() {}
        virtual Document* convertPDF2Image(Document* pdf, int dpi) throw(PDLSException) = 0;
    };

}

#endif //CONTENTEXTRACTIONMODULE_PDF2IMGCONVERSIONINTERFACE_H
