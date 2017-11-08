#ifndef PRINTEDDOCUMENTVERIFICATIONSYSTEM_IPDF2TEXTCONVERTER_H
#define PRINTEDDOCUMENTVERIFICATIONSYSTEM_IPDF2TEXTCONVERTER_H

#include "../Datatypes/Document.h"

namespace PDLS {

    struct IPDF2TextConverter {
        virtual ~IPDF2TextConverter() {}
        virtual Document* convertPDF2Text(Document* pdf) throw(PDLSException) = 0;
    };

}

#endif //PRINTEDDOCUMENTVERIFICATIONSYSTEM_IPDF2TEXTCONVERTER_H
