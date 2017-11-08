#include "LDataLoadingModule.h"

#include "../Datatypes/Document.h"
#include "../Datatypes/EnumTypes.h"
#include "../Datatypes/Link.h"

namespace PDLS {

    LinkingData* LDataLoadingModule::loadLinkingData(Link* link) throw(PDLSException) {
        if(!link)
            throw NullPointerException("IPFSLDataLoader::downloadLinkingData");
        return _provider->downloadLinkingData(link);
    }

}

