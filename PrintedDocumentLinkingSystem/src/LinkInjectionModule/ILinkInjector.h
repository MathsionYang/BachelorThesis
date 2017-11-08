#ifndef PRINTEDDOCUMENTVERIFICATIONSYSTEM_ILDataLINKINJECTIONSTRATEGY_H
#define PRINTEDDOCUMENTVERIFICATIONSYSTEM_ILDataLINKINJECTIONSTRATEGY_H

#include "../Datatypes/Document.h"
#include "../Datatypes/LinkingData.h"
#include "../Datatypes/Link.h"

namespace PDLS {

    struct ILinkInjector {
        virtual void injectLink(Document* doc, Link* l, const bfs::path& out) throw(PDLSException) = 0;
        virtual ~ILinkInjector() {}
    };

}

#endif //PRINTEDDOCUMENTVERIFICATIONSYSTEM_ILDataLINKINJECTIONSTRATEGY_H
