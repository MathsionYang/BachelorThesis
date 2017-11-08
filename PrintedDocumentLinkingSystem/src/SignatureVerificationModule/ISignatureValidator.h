#ifndef PRINTEDDOCUMENTVERIFICATIONSYSTEM_SIGNATUREVERIFICATIONSTRATEGY_H
#define PRINTEDDOCUMENTVERIFICATIONSYSTEM_SIGNATUREVERIFICATIONSTRATEGY_H


#include "../Datatypes/PDLSException.h"
#include "../Datatypes/Signature.h"
#include "../Datatypes/X509Certificate.h"
#include "../Datatypes/EnumTypes.h"

namespace PDLS {

    struct ISignatureValidator {
        virtual ValidationState validateSignature(ContentHash* contentHash, Signature* sig, X509Certificate* x509) throw(PDLSException)  = 0;
        virtual ~ISignatureValidator() {}
    };

}


#endif //PRINTEDDOCUMENTVERIFICATIONSYSTEM_SIGNATUREVERIFICATIONSTRATEGY_H
