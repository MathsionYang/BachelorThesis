#include "SignatureVerificationModule.h"

namespace PDLS {


    SignatureVerificationState SignatureVerificationModule::verifySignature(Document* doc, X509Certificate* x509) throw(PDLSException) {
        Signature* sig = doc->getSignature();
        ContentHash* chash = doc->getContentHash();
        return verifySignature(chash, sig, x509);
    }

    SignatureVerificationState SignatureVerificationModule::verifySignature(ContentHash* cHash, Signature* sig,
                                                                            X509Certificate* x509) throw(PDLSException) {
        if(_signatureValidationStrategy == nullptr || _certificateValidationStrategy == nullptr)
            throw NoStrategyException("SVM");

        ValidationState certValidationState = _certificateValidationStrategy->validateCertificate(
                x509);
        ValidationState sigValidationState = _signatureValidationStrategy->validateSignature(cHash, sig, x509);

        return evaluateSignatureVerificationState(certValidationState, sigValidationState);
    }

    const SignatureVerificationState SignatureVerificationModule::evaluateSignatureVerificationState(
            ValidationState certificateVerificationStateState,
            ValidationState signatureVerificationState) const {

        switch (certificateVerificationStateState) {
            case ValidationState::VALID:
                switch (signatureVerificationState) {
                    case ValidationState::VALID:
                        return SignatureVerificationState::CERT_VALID_SIG_VALID;
                    case ValidationState::INVALID:
                        return SignatureVerificationState::CERT_VALID_SIG_INVALID;
                }
            case ValidationState::INVALID:
                switch (signatureVerificationState) {
                    case ValidationState::VALID:
                        return SignatureVerificationState::CERT_INVALID_SIG_VALID;
                    case ValidationState::INVALID:
                        return SignatureVerificationState::CERT_INVALID_SIG_INVALID;
                }
        }
    }


}

