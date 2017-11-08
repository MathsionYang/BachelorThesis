#ifndef PRINTEDDOCUMENTVERIFICATIONSYSTEM_RSASIGNATUREGENERATION_H
#define PRINTEDDOCUMENTVERIFICATIONSYSTEM_RSASIGNATUREGENERATION_H

#include "../Datatypes/RSAKey.h"
#include "../Datatypes/Signature.h"
#include "ISignatureGenerator.h"

namespace PDLS {

    class OpenSSLSignatureGenerator : public ISignatureGenerator {
    public:
        virtual Signature* generateSignature(ContentHash* doc, RSAPrivateKey* pK) throw (PDLSException) override;
    };

}


#endif //PRINTEDDOCUMENTVERIFICATIONSYSTEM_RSASIGNATUREGENERATION_H
