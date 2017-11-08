#ifndef PRINTEDDOCUMENTVERIFICATIONSYSTEM_ILDataEXTRACTIONSTRATEGY_H
#define PRINTEDDOCUMENTVERIFICATIONSYSTEM_ILDataEXTRACTIONSTRATEGY_H

#include "../Datatypes/Document.h"
#include "../Util/IProvider.h"
#include "../Datatypes/Link.h"
#include "../Datatypes/LinkDescription.h"

namespace PDLS {

    class ILinkExtractor {
    public:
        virtual Link* extractLink(Document* doc, LinkDescription* desc) throw(PDLSException) = 0;
        virtual ~ILinkExtractor() {}
    };

}

#endif //PRINTEDDOCUMENTVERIFICATIONSYSTEM_ILDataEXTRACTIONSTRATEGY_H
