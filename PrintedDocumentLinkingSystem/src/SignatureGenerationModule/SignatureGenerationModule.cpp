#include "SignatureGenerationModule.h"

namespace PDLS {

    Signature* SignatureGenerationModule::generateSignature(ContentHash* cHash, RSAPrivateKey* pK) throw(PDLSException) {
        if(_strategy == nullptr)
            throw NoStrategyException("SGM");
        if(pK == nullptr)
            throw MissingPrivateKeyException();

        return _strategy->generateSignature(cHash, pK);
    }

}
