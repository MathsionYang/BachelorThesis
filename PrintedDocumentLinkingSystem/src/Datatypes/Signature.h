#ifndef PRINTEDDOCUMENTVERIFICATIONSYSTEM_DOCUMENTSIGNATURE_H
#define PRINTEDDOCUMENTVERIFICATIONSYSTEM_DOCUMENTSIGNATURE_H

#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/ssl.h>

#include "PDLSException.h"
#include "RSAKey.h"

namespace PDLS {

    class ContentHash;

    class Signature {
    public:

        struct ByteSignature {
            size_t size;
            unsigned char* data;
            ByteSignature() : data(nullptr) { };
            ~ByteSignature() { if(data != nullptr) free(data); };
        };

    private:

        const ContentHash* _source;
        ByteSignature* _byteSignature;
        std::string _base64Signature;

        void encodeByteToBase64Signature() {
            if (_byteSignature != nullptr) {
                BIO* memoryBioPtr = nullptr;
                BIO* b64BioPtr = nullptr;
                BUF_MEM* bufferPtr = nullptr;

                b64BioPtr = BIO_new(BIO_f_base64());
                memoryBioPtr = BIO_new(BIO_s_mem());
                memoryBioPtr = BIO_push(b64BioPtr, memoryBioPtr);

                BIO_write(memoryBioPtr, _byteSignature->data, static_cast<unsigned>(_byteSignature->size));
                BIO_flush(memoryBioPtr);
                BIO_get_mem_ptr(memoryBioPtr, & bufferPtr);
                BIO_set_close(memoryBioPtr, BIO_NOCLOSE);

                std::stringstream ss;
                for (unsigned i = 0; i < bufferPtr->length; i++) {
                    ss << bufferPtr->data[i];
                }

                _base64Signature = ss.str();

                BIO_free_all(memoryBioPtr);
            }
        }

        size_t calculateBase64DecodeLength(const char* b64input) {
            size_t len = strlen(b64input), padding = 0;

            if (b64input[len-1] == '=' && b64input[len-2] == '=') //last two chars are =
                padding = 2;
            else if (b64input[len-1] == '=') //last char is =
                padding = 1;
            return (len*3)/4 - padding;
        }

        void decodeBase64ToByteSignature() {
            if (_base64Signature.size() != 0) {

                if(_byteSignature == nullptr) _byteSignature = new ByteSignature;

                BIO* memoryBioPtr = nullptr;
                BIO* b64BioPtr = nullptr;

                size_t decodeLength = calculateBase64DecodeLength(_base64Signature.c_str());

                _byteSignature->data = (unsigned char*)malloc(decodeLength + 1);
                _byteSignature->data[decodeLength] = '\0';

                b64BioPtr = BIO_new(BIO_f_base64());
                memoryBioPtr = BIO_new_mem_buf(_base64Signature.c_str(), -1);
                memoryBioPtr = BIO_push(b64BioPtr, memoryBioPtr);

                //TODO when do I now if flag has to be set or not?! for all general cases
                //BIO_set_flags(memoryBioPtr, BIO_FLAGS_BASE64_NO_NL); //Do not use newlines to flush buffer
                _byteSignature->size = static_cast<size_t>(BIO_read(memoryBioPtr, _byteSignature->data, static_cast<int>(_base64Signature.size())));

                BIO_free_all(memoryBioPtr);
            }
        }

    public:

        Signature(const ContentHash* p) : _source(p), _byteSignature(nullptr), _base64Signature("") { }
        Signature(const std::string& b64Sig) : _source(nullptr), _byteSignature(nullptr), _base64Signature(b64Sig) { }

        const ContentHash* getSource() const {
            return _source;
        }

        const std::string& getBase64Signature() {
            if(_base64Signature.size() == 0) encodeByteToBase64Signature();
            return _base64Signature;
        }

        ByteSignature* getByteSignature() {
            if(_byteSignature == nullptr) decodeBase64ToByteSignature();
            return _byteSignature;
        }

        void setByteSignature(ByteSignature* byteSignature) {
            encodeByteToBase64Signature();
            _byteSignature = byteSignature;
        }

        void setBase64Signature(const std::string& base64Signature) {
            _base64Signature = base64Signature;
        }
    };
}

#endif //PRINTEDDOCUMENTVERIFICATIONSYSTEM_DOCUMENTSIGNATURE_H
