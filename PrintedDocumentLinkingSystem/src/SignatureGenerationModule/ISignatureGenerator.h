#ifndef PRINTEDDOCUMENTVERIFICATIONSYSTEM_SIGNATUREGENERATIONSTRATEGY_H
#define PRINTEDDOCUMENTVERIFICATIONSYSTEM_SIGNATUREGENERATIONSTRATEGY_H

#include "../Datatypes/PDLSException.h"

namespace PDLS {

    struct ISignatureGenerator {
        virtual Signature* generateSignature(ContentHash* doc, RSAPrivateKey* pK) throw(PDLSException) = 0;
        virtual ~ISignatureGenerator() {}
    };

}

#endif //PRINTEDDOCUMENTVERIFICATIONSYSTEM_SIGNATUREGENERATIONSTRATEGY_H
