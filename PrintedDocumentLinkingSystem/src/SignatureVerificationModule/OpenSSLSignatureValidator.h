#ifndef PRINTEDDOCUMENTVERIFICATIONSYSTEM_RSASIGNATUREVERIFICATOR_H
#define PRINTEDDOCUMENTVERIFICATIONSYSTEM_RSASIGNATUREVERIFICATOR_H

#include "ISignatureValidator.h"
#include "../Datatypes/Document.h"
#include "../Datatypes/ContentHash.h"
#include "../Datatypes/Signature.h"
#include "../Datatypes/EnumTypes.h"


namespace PDLS {

    class OpenSSLSignatureValidator : public ISignatureValidator {
    public:
        virtual ValidationState validateSignature(ContentHash* contentHash, Signature* sig, X509Certificate* x509) throw(PDLSException) override;
    };

}

#endif //PRINTEDDOCUMENTVERIFICATIONSYSTEM_RSASIGNATUREVERIFICATOR_H
