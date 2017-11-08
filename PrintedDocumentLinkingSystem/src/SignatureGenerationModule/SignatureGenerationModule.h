#ifndef PRINTEDDOCUMENTVERIFICATIONSYSTEM_SIGNATUREGENERATIONMODULE_H
#define PRINTEDDOCUMENTVERIFICATIONSYSTEM_SIGNATUREGENERATIONMODULE_H
#include <iostream>

#include "../Datatypes/ContentHash.h"
#include "../Datatypes/RSAKey.h"
#include "../Datatypes/Signature.h"

#include "ISignatureGenerator.h"
#include "OpenSSLSignatureGenerator.h"

namespace PDLS {

    class SignatureGenerationModule {
        ISignatureGenerator* _strategy;

        SignatureGenerationModule() : _strategy(nullptr) { createDefaultStrategy(); }

    public:
        static SignatureGenerationModule* getInstance() {
            static SignatureGenerationModule singleton;
            return &singleton;
        }

        Signature* generateSignature(ContentHash* cHash, RSAPrivateKey* pK) throw(PDLSException);

        inline void createDefaultStrategy() {
            _strategy = new OpenSSLSignatureGenerator();
        }

        inline const  ISignatureGenerator* getStrategy() const {
            return _strategy;
        }

        inline void setStrategy(ISignatureGenerator* strategy) {
            _strategy = strategy;
        }

        SignatureGenerationModule(const SignatureGenerationModule&) = delete;
        void operator=(const SignatureGenerationModule&) = delete;
    };

}

#endif //PRINTEDDOCUMENTVERIFICATIONSYSTEM_SIGNATUREGENERATIONMODULE_H
