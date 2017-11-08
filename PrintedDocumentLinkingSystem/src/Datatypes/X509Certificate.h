#ifndef PRINTEDDOCUMENTVERIFICATIONSYSTEM_X509CERTIFICATE_H
#define PRINTEDDOCUMENTVERIFICATIONSYSTEM_X509CERTIFICATE_H

#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/pem.h>
#include <openssl/x509.h>
#include "../Datatypes/File.h"

namespace PDLS {

    class X509Certificate final {
        bool _isSelfSigned;
        File* _pem;
        std::string _certData;

        X509* _openSSLX509;
        EVP_PKEY* _openSSLEVPPublicKey;
        RSA* _openSSLRSAPublicKey;

        void createOpenSSLX509() {
            //create openssl x509 object from pem
            BIO* bio_mem = BIO_new(BIO_s_mem());

            if(!_pem && _certData.size() != 0)
                BIO_puts(bio_mem, _certData.c_str());
            else
                BIO_puts(bio_mem, _pem->getContentAsString().c_str());

            X509* x509Object = PEM_read_bio_X509(bio_mem, NULL, NULL, NULL);

            if(x509Object == nullptr)
                throw OpenSSLX509ObjectCreationException(_pem->getPath());

            //free bio
            BIO_free(bio_mem);

            _openSSLX509 = x509Object;
        }

        EVP_PKEY* extractOpenSSLEVPPublicKey() throw(PDLSException) {
            if(_openSSLX509 == nullptr)
                createOpenSSLX509();

            //get evp public key from certificate
            EVP_PKEY* pkey=X509_get_pubkey(_openSSLX509);

            if(pkey == nullptr)
                throw OpenSSLEVPKeyObjectExtractionException(_pem->getPath());

            _openSSLEVPPublicKey = pkey;
        }

        RSA* extractOpenSSLRSAPublicKey() throw (PDLSException) {

            if(_openSSLEVPPublicKey == nullptr)
                extractOpenSSLEVPPublicKey();

            //get rsa public key from evp public key
            RSA* rsaPubKey = EVP_PKEY_get1_RSA(_openSSLEVPPublicKey);

            if(rsaPubKey == nullptr)
                OpenSSLRSAPublicKeyObjectExtractionException(_pem->getPath());

            return rsaPubKey;
        }

    public:

        X509Certificate(File* pem, bool isSelfSigned=true) : _pem(pem), _isSelfSigned(isSelfSigned), _openSSLX509(nullptr), _openSSLEVPPublicKey(nullptr) {
            //init openssl
            OpenSSL_add_all_algorithms();
            ERR_load_BIO_strings();
            ERR_load_crypto_strings();
        }

        X509Certificate(const std::string& data, bool isSelfSigned=true) : _pem(nullptr), _certData(data), _isSelfSigned(isSelfSigned), _openSSLX509(nullptr), _openSSLEVPPublicKey(nullptr) {
            //init openssl
            OpenSSL_add_all_algorithms();
            ERR_load_BIO_strings();
            ERR_load_crypto_strings();
        }

        ~X509Certificate() {
            if(_openSSLX509 != nullptr)
                X509_free(_openSSLX509);
            if(_openSSLEVPPublicKey != nullptr)
                EVP_PKEY_free(_openSSLEVPPublicKey);
            if(_openSSLRSAPublicKey != nullptr)
                RSA_free(_openSSLRSAPublicKey);
            if(_pem) delete _pem;
        }

        X509* getOpenSSLX509() {
            if(_openSSLX509 == nullptr) createOpenSSLX509();
            return _openSSLX509;
        }

        RSA* getOpenSSLRSAPublicKey() {
            if(_openSSLEVPPublicKey == nullptr) extractOpenSSLRSAPublicKey();
            return _openSSLRSAPublicKey;
        }

        EVP_PKEY* getOpenSSLEVPPublicKey() {
            if(_openSSLEVPPublicKey == nullptr) extractOpenSSLEVPPublicKey();
            return _openSSLEVPPublicKey;
        }

        bool isSelfSigned() const {
            return _isSelfSigned;
        }

        File* getPem() const {
            return _pem;
        }
    };

}

#endif //PRINTEDDOCUMENTVERIFICATIONSYSTEM_X509CERTIFICATE_H
