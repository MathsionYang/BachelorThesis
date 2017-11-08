#include "DocumentLinkingModule.h"

namespace PDLS {

    Link* DocumentLinkingModule::linkDocument(LinkingData* ldata) throw(PDLSException){
        if(_provider == nullptr)
            throw NoProviderException("DLM");

        return _provider->uploadLinkingData(ldata);
    }

    Link* DocumentLinkingModule::linkDocument(Document* doc, X509Certificate* cert) throw(PDLSException) {
        if(!doc)
            throw NullPointerException("DocumentLinkingModule::linkDocument");
        if(doc->getSignature() == nullptr)
            throw LDataMissingSignatureException();
        else if(doc->getContentHash() == nullptr)
            throw LDataMissingContentHashException();
        else if(!cert)
            throw LDataMissingX509CertificateException();

        LinkingData* ldata = new LinkingData(doc, cert);

        return linkDocument(ldata);
    }
}
