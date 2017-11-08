#include "OpenSSLSignatureGenerator.h"

#include "../Datatypes/ContentHash.h"
#include "../Datatypes/Content.h"

namespace PDLS {
    Signature* OpenSSLSignatureGenerator::generateSignature(ContentHash* ch, RSAPrivateKey* pK) throw(PDLSException) {

        if(pK == nullptr)
            throw MissingPrivateKeyException();

        //get msg to encrypt
        const char* msg = ch->getStringHash().c_str();

        //get openssl rsa key
        RSA* rsaPK = pK->createOpenSSLRSAKeyObject();

        //create openssl signing context
        EVP_MD_CTX* rsaSignCtx = EVP_MD_CTX_create();
        EVP_PKEY* priKey  = EVP_PKEY_new();
        EVP_PKEY_assign_RSA(priKey, rsaPK);

        //init ctxt
        if (EVP_SignInit(rsaSignCtx, EVP_sha256()) <=0)
            throw RSASignatureGenerationException();

        //add data to sign
        if (EVP_SignUpdate(rsaSignCtx, msg, std::strlen(msg)) <= 0) {
            throw RSASignatureGenerationException();
        }

        //create result byte signature struct
        Signature::ByteSignature* byteSig = new Signature::ByteSignature();
        //alloc buffer memory
        byteSig->data = (unsigned char*)malloc(byteSig->size);

        //do signing
        if (EVP_SignFinal(rsaSignCtx, byteSig->data, (unsigned int*) &byteSig->size, priKey) <= 0)
            throw RSASignatureGenerationException();


        Signature* res = new Signature(ch);
        res->setByteSignature(byteSig);

        EVP_MD_CTX_destroy(rsaSignCtx);
        //TODO open SSL Memory leaks -> where to free open ssl stuff?!

        return res;
    }

}


