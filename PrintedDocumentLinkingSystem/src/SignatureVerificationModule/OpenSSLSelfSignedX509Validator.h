#ifndef PRINTEDDOCUMENTVERIFICATIONSYSTEM_SELFSIGNEDX509VERIFICATOR_H
#define PRINTEDDOCUMENTVERIFICATIONSYSTEM_SELFSIGNEDX509VERIFICATOR_H

#include "ICertificateValidator.h"
#include "../Datatypes/X509Certificate.h"
#include "../Datatypes/PDLSException.h"
#include "../Datatypes/EnumTypes.h"

namespace PDLS {

    class OpenSSLSelfSignedX509Validator : public ICertificateValidator {
    public:
        virtual ValidationState validateCertificate(X509Certificate* x509) throw(PDLSException) override {
            return (X509_verify(x509->getOpenSSLX509(), x509->getOpenSSLEVPPublicKey()) <= 0) ?
                   ValidationState::INVALID : ValidationState::VALID;
        }
    };

}

#endif //PRINTEDDOCUMENTVERIFICATIONSYSTEM_SELFSIGNEDX509VERIFICATOR_H
