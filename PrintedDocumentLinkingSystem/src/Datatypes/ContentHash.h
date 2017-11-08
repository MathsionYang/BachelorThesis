#ifndef PRINTEDDOCUMENTVERIFICATIONSYSTEM_DOCUMENTCONTENTHASH_H
#define PRINTEDDOCUMENTVERIFICATIONSYSTEM_DOCUMENTCONTENTHASH_H

#include <iomanip>
#include <iostream>
#include <sstream>

#include <openssl/evp.h>

#include "PDLSException.h"
#include "EnumTypes.h"

namespace PDLS {

    class ContentHash {
    public:
        struct RawByteHash {
            unsigned char* _data;
            unsigned int _size;

            explicit RawByteHash() : _data(nullptr), _size(0) {}
            ~RawByteHash(){ if(_data != nullptr) OPENSSL_free(_data); }

            void operator=(const RawByteHash&) = delete;
            RawByteHash(const RawByteHash&) = delete;
        };

    private:

        ContentHashType _type;
        RawByteHash* _rawByteHash;
        std::string _stringHash;
        std::string _prefix;
        std::string _postfix;

        void convertRawByteToStringHash();
        void convertStringToRawByteHash();

        void validateStringHash();

        void trimPrefixFromStringHashInput();
        void trimPostfixFromStringHashInput();

    public:


        ContentHash(ContentHashType t, const std::string& stringHash, const std::string& prefix, const std::string& postfix) : _type(t),
                                                                                                                        _rawByteHash(nullptr),
                                                                                                                        _stringHash(stringHash),
                                                                                                                        _prefix(prefix),
                                                                                                                        _postfix(postfix) {
            trimPrefixFromStringHashInput();
            trimPostfixFromStringHashInput();
            validateStringHash();
            convertStringToRawByteHash();
        }

        ContentHash(ContentHashType t, RawByteHash* raw, const std::string& prefix, const std::string& postfix) : _type(t),
                                                                                                            _rawByteHash(raw),
                                                                                                            _stringHash(""),
                                                                                                            _prefix(prefix),
                                                                                                            _postfix(postfix) {
            convertRawByteToStringHash();
            validateStringHash();
        }

        ContentHashType getType() const {
            return _type;
        }

        void setByteHash(RawByteHash* bH) {
            _rawByteHash = bH;
            convertRawByteToStringHash();
        }

        RawByteHash* getByteHash() {
            return _rawByteHash;
        }

        const std::string& getStringHash() const {
            return _stringHash;
        }

        const std::string& getPrefix() const {
            return _prefix;
        }

        const std::string& getPostfix() const {
            return _postfix;
        }

        std::string getTypeString() const {
            switch(_type) {
                case ContentHashType::MD5: return "MD5";
                case ContentHashType::SHA1: return "SHA1";
                case ContentHashType::SHA224: return "SHA224";
                case ContentHashType::SHA256: return "SHA256";
                case ContentHashType::SHA384: return "SHA384";
                case ContentHashType::SHA512: return "SHA512";
            }
        }

        static std::string getTypeString(ContentHashType t) {
            switch(t) {
                case ContentHashType::MD5: return "MD5";
                case ContentHashType::SHA1: return "SHA1";
                case ContentHashType::SHA224: return "SHA224";
                case ContentHashType::SHA256: return "SHA256";
                case ContentHashType::SHA384: return "SHA384";
                case ContentHashType::SHA512: return "SHA512";
            }
        }

        static ContentHashType getTypeFromString(const std::string& t) {
            if(t == "MD5")
                return ContentHashType::MD5;
            else if(t ==  "SHA1")
                return ContentHashType::SHA1;
            else if(t ==  "SHA224")
                return ContentHashType::SHA224;
            else if(t ==  "SHA256")
                return ContentHashType::SHA256;
            else if(t ==  "SHA384")
                return ContentHashType::SHA384;
            else if(t ==  "SHA512")
                return ContentHashType::SHA512;
            else //default
                return ContentHashType::SHA256;
        }
    };
}

#endif //PRINTEDDOCUMENTVERIFICATIONSYSTEM_DOCUMENTCONTENTHASH_H
