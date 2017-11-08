#ifndef PRINTEDDOCUMENTVERIFICATIONSYSTEM_SIGNATUREVERIFICATIONMODULE_H
#define PRINTEDDOCUMENTVERIFICATIONSYSTEM_SIGNATUREVERIFICATIONMODULE_H


#include "../Datatypes/Signature.h"
#include "../Datatypes/Document.h"
#include "../Datatypes/EnumTypes.h"
#include "../Datatypes/X509Certificate.h"

#include "ISignatureValidator.h"
#include "OpenSSLSignatureValidator.h"
#include "ICertificateValidator.h"
#include "OpenSSLSelfSignedX509Validator.h"

namespace PDLS {

    class SignatureVerificationModule {

        const SignatureVerificationState evaluateSignatureVerificationState(
                ValidationState state,
                ValidationState verificationState) const;

        ISignatureValidator* _signatureValidationStrategy;
        ICertificateValidator* _certificateValidationStrategy;

        SignatureVerificationModule() : _signatureValidationStrategy(nullptr), _certificateValidationStrategy(nullptr) { createDefaultStrategies(); }

    public:

        static SignatureVerificationModule* getInstance() {
            static SignatureVerificationModule singleton;
            return &singleton;
        }

        SignatureVerificationState verifySignature(Document* doc, X509Certificate* x509) throw(PDLSException);
        SignatureVerificationState verifySignature(ContentHash* cHash, Signature* sig, X509Certificate* x509) throw(PDLSException);

        ISignatureValidator* createDefaultStrategies() {
            if(_signatureValidationStrategy != nullptr) delete _signatureValidationStrategy;
            _signatureValidationStrategy = new OpenSSLSignatureValidator();

            if(_certificateValidationStrategy != nullptr) delete _certificateValidationStrategy;
            _certificateValidationStrategy = new OpenSSLSelfSignedX509Validator();
        }

        SignatureVerificationModule(const SignatureVerificationModule&) = delete;
        void operator=(const SignatureVerificationModule&) = delete;

    };

}

#endif //PRINTEDDOCUMENTVERIFICATIONSYSTEM_SIGNATUREVERIFICATIONMODULE_H
