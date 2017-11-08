#include "OpenSSLSignatureValidator.h"

namespace PDLS {

    ValidationState OpenSSLSignatureValidator::validateSignature(ContentHash* contentHash, Signature* sig,
                                                               X509Certificate* x509) throw(PDLSException) {
        if(sig == nullptr)
            throw SVMMissingSignatureException();
        if(x509 == nullptr)
            throw SVMMissingCertificateException();
        if(contentHash == nullptr)
            throw SVMMissingContentHashException();

        //create rsa signature verification context
        EVP_MD_CTX* rsaVerifyCtx = EVP_MD_CTX_create();

        //init context
        if (EVP_VerifyInit(rsaVerifyCtx, EVP_sha256()) <= 0)
            throw PDLSException();

        //add cHash to ctx
        if(EVP_VerifyUpdate(rsaVerifyCtx, contentHash->getStringHash().c_str(), contentHash->getStringHash().size()) <= 0)
            throw PDLSException();

        //to the verification and save the result in authFlag
        bool authFlag = EVP_VerifyFinal(rsaVerifyCtx, sig->getByteSignature()->data, static_cast<int>(sig->getByteSignature()->size), x509->getOpenSSLEVPPublicKey()) > 0;

        //destroy rsa signature verification context
        EVP_MD_CTX_destroy(rsaVerifyCtx);

        return authFlag ? ValidationState::VALID : ValidationState::INVALID;
    }

}

