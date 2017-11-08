#include "OpenSSLContentHashGenerator.h"

#include <openssl/evp.h>
#include <openssl/err.h>

#include <iostream>

namespace PDLS {

    ContentHash* OpenSSLContentHashGenerator::generateContentHash(NormalizedContent* sdc) throw(PDLSException) {

        //https://wiki.openssl.org/index.php/EVP_Message_Digests

        OpenSSL_add_all_digests();
        ERR_load_BIO_strings();
        ERR_load_crypto_strings();


        ContentHash::RawByteHash* byteHash= new ContentHash::RawByteHash;

        EVP_MD_CTX *mdctx;

        if((mdctx = EVP_MD_CTX_create()) == NULL)
            throw ContentHashGenerationException();

        switch (_hashType) {
            case ContentHashType::MD5:
                if(1 != EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL))
                    throw ContentHashGenerationException();

                if((byteHash->_data = (unsigned char *)OPENSSL_malloc(EVP_MD_size(EVP_md5()))) == NULL)
                    throw ContentHashGenerationException();
                break;
            case ContentHashType::SHA1:
                if(1 != EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL))
                    throw ContentHashGenerationException();

                if((byteHash->_data = (unsigned char *)OPENSSL_malloc(EVP_MD_size(EVP_sha1()))) == NULL)
                    throw ContentHashGenerationException();
                break;
            case ContentHashType::SHA224:
                if(1 != EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL))
                    throw ContentHashGenerationException();

                if((byteHash->_data = (unsigned char *)OPENSSL_malloc(EVP_MD_size(EVP_sha224()))) == NULL)
                    throw ContentHashGenerationException();
                break;
            case ContentHashType::SHA256:
                if(1 != EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL))
                    throw ContentHashGenerationException();

                if((byteHash->_data = (unsigned char *)OPENSSL_malloc(EVP_MD_size(EVP_sha256()))) == NULL)
                    throw ContentHashGenerationException();
                break;
            case ContentHashType::SHA384:
                if(1 != EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL))
                    throw ContentHashGenerationException();

                if((byteHash->_data = (unsigned char *)OPENSSL_malloc(EVP_MD_size(EVP_sha384()))) == NULL)
                    throw ContentHashGenerationException();
                break;
            case ContentHashType::SHA512:
                if(1 != EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL))
                    throw ContentHashGenerationException();

                if((byteHash->_data = (unsigned char *)OPENSSL_malloc(EVP_MD_size(EVP_sha512()))) == NULL)
                    throw ContentHashGenerationException();
                break;
        }

        if(1 != EVP_DigestUpdate(mdctx, sdc->getValue().c_str(), sdc->getValue().size()))
            throw ContentHashGenerationException();

        if(1 != EVP_DigestFinal_ex(mdctx, byteHash->_data, &byteHash->_size))
            throw ContentHashGenerationException();

        EVP_MD_CTX_destroy(mdctx);

        ContentHash* res = new ContentHash(_hashType, byteHash, _hashPrefix, _hashPostfix);

        sdc->getOwner()->setContentHash(res);

        return res;
    }
}
