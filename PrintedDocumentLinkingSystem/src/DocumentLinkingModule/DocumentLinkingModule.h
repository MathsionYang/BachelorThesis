#ifndef PRINTEDDOCUMENTVERIFICATIONSYSTEM_DOCUMENTREGISTRATIONMODULE_H
#define PRINTEDDOCUMENTVERIFICATIONSYSTEM_DOCUMENTREGISTRATIONMODULE_H

#include "../Datatypes/Document.h"
#include "../Util/IProvider.h"
#include "../Datatypes/EnumTypes.h"

#include "../Datatypes/Link.h"
#include "../Util/IPFSProvider.h"

namespace PDLS {

    class DocumentLinkingModule {

        IProvider* _provider;

        DocumentLinkingModule() : _provider(IPFSProvider::getInstance()) {}

    public:

        static DocumentLinkingModule* getInstance() {
            static  DocumentLinkingModule singleton;
            return &singleton;
        }

        Link* linkDocument(LinkingData* ldata) throw(PDLSException);
        Link* linkDocument(Document* doc, X509Certificate* cert) throw(PDLSException);


        inline IProvider* getProvider() const {
            return _provider;
        }

        inline void setProvider(IProvider* provider) {
            _provider = provider;
        }

        DocumentLinkingModule(const DocumentLinkingModule&) = delete;
        void operator=(const DocumentLinkingModule&) = delete;
    };

}

#endif //PRINTEDDOCUMENTVERIFICATIONSYSTEM_DOCUMENTREGISTRATIONMODULE_H
