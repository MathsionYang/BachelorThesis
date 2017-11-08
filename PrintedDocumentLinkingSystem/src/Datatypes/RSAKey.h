#ifndef PRINTEDDOCUMENTVERIFICATIONSYSTEM_CRYPTOGRAPHICKEY_H
#define PRINTEDDOCUMENTVERIFICATIONSYSTEM_CRYPTOGRAPHICKEY_H

#include "File.h"
#include "X509Certificate.h"
#include "EnumTypes.h"

#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/bio.h>
#include <openssl/rsa.h>

namespace PDLS {

    class RSAKey {
    protected:
        File* _pem;
    public:
        RSAKey(File* pem) : _pem(pem) {}

        virtual RSA* createOpenSSLRSAKeyObject() throw (PDLSException) = 0;

        inline File* getPem() const {
            return _pem;
        }
    };

    class RSAPrivateKey : public RSAKey {
    public:
        RSAPrivateKey(File* pem) : RSAKey(pem) {}

        virtual RSA* createOpenSSLRSAKeyObject() throw (PDLSException) override {
            RSA* rsa = NULL;
            const char* c_string = _pem->getContentAsString().c_str();
            BIO * keybio = BIO_new_mem_buf((void*)c_string, -1);

            if (keybio==NULL)
                throw OpenSSLRSAPrivateKeyObjectCreationException(_pem->getPath());

            rsa = PEM_read_bio_RSAPrivateKey(keybio, &rsa, NULL, NULL);

            if(rsa == nullptr)
                throw OpenSSLRSAPrivateKeyObjectCreationException(_pem->getPath());

            return rsa;
        }

    };

    class RSAPublicKey : public RSAKey {
        X509Certificate* _parentCert;

    public:
        RSAPublicKey(X509Certificate* cert) : RSAKey(cert->getPem()), _parentCert(cert) {}

        virtual RSA* createOpenSSLRSAKeyObject() throw (PDLSException) override {
            _parentCert->getOpenSSLRSAPublicKey();
        }

    };

}

#endif //PRINTEDDOCUMENTVERIFICATIONSYSTEM_CRYPTOGRAPHICKEY_H
