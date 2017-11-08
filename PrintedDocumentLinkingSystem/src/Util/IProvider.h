#ifndef PRINTEDDOCUMENTVERIFICATIONSYSTEM_IPROVIDER_H
#define PRINTEDDOCUMENTVERIFICATIONSYSTEM_IPROVIDER_H

#include "../Datatypes/PDLSException.h"
#include "../Datatypes/LinkingData.h"
#include "../Datatypes/LinkDescription.h"

namespace PDLS {

    //forward decl
    class Link;

    struct IProvider {
        virtual ~IProvider() {}
        virtual Link* uploadLinkingData(LinkingData* ldata) throw(PDLSException) = 0;
        virtual LinkingData* downloadLinkingData(Link* link) throw(PDLSException) = 0;
        virtual LinkDescription* getSupportedLinkDescription() = 0;
    };

}

#endif //PRINTEDDOCUMENTVERIFICATIONSYSTEM_IPROVIDER_H
