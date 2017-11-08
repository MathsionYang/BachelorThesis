#ifndef PRINTEDDOCUMENTVERIFICATIONSYSTEM_LDataLOADERMODULE_H
#define PRINTEDDOCUMENTVERIFICATIONSYSTEM_LDataLOADERMODULE_H

#include <set>

#include "../Datatypes/LinkingData.h"
#include "../Datatypes/Link.h"
#include "../Util/IPFSProvider.h"

namespace PDLS {

    class LDataLoadingModule {

        LDataLoadingModule() : _provider(IPFSProvider::getInstance()) { }

        IProvider* _provider;

    public:
        LinkingData* loadLinkingData(Link* link)  throw(PDLSException);


        inline IProvider* getProvider() const {
            return _provider;
        }

        inline void setProvider(IProvider* provider) {
            _provider = provider;
        }

        static LDataLoadingModule* getInstance() {
            static LDataLoadingModule singleton;
            return &singleton;
        }

        LDataLoadingModule(const LDataLoadingModule&) = delete;
        void operator=(const LDataLoadingModule&) = delete;

    };

}

#endif //PRINTEDDOCUMENTVERIFICATIONSYSTEM_LDataLOADERMODULE_H
