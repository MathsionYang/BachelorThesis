#include <boost/algorithm/string.hpp>
#include "ContentHash.h"

namespace PDLS {

    void ContentHash::convertStringToRawByteHash() {
        if(_stringHash != "") {
            if(_rawByteHash != nullptr) delete _rawByteHash;

            _rawByteHash = new RawByteHash;

            //copy string hash c_str no non const buffer
            char *buffer = new char[_stringHash.size()];
            std::copy(_stringHash.c_str(), _stringHash.c_str() + _stringHash.size(), buffer);

            //reinterpret char* to unsigned char* proper for byte representation
            _rawByteHash->_data = reinterpret_cast<unsigned char*>(buffer);

            switch (_type) {
                // x bits/8 <=> conversion bits to byte
                case ContentHashType::MD5:
                    _rawByteHash->_size = 128/8;
                    break;
                case ContentHashType::SHA1:
                    _rawByteHash->_size = 160/8;
                    break;
                case ContentHashType::SHA224:
                    _rawByteHash->_size = 224/8;
                    break;
                case ContentHashType::SHA256:
                    _rawByteHash->_size = 256/8;
                    break;
                case ContentHashType::SHA384:
                    _rawByteHash->_size = 384/8;
                    break;
                case ContentHashType::SHA512:
                    _rawByteHash->_size = 512/8;
                    break;
            }
        }
    }

    void ContentHash::validateStringHash()  {
        //string contains 1 char per hex digit
        //1 byte <=> 8 bits <=> 2 hex digits ==> x bits / 8 / 2 = x bits / 4 <=> number of hex digits
        switch (_type){
            case ContentHashType::MD5:
                if(_stringHash.size() != 128/4)
                    throw InvalidContentHashException(_stringHash, _prefix, _postfix);
                break;
            case ContentHashType::SHA1:
                if(_stringHash.size() != 160/4)
                    throw InvalidContentHashException(_stringHash, _prefix, _postfix);
                break;
            case ContentHashType::SHA224:
                if(_stringHash.size() != 224/4)
                    throw InvalidContentHashException(_stringHash, _prefix, _postfix);
                break;
            case ContentHashType::SHA256:
                if(_stringHash.size() != 256/4)
                    throw InvalidContentHashException(_stringHash, _prefix, _postfix);
                break;
            case ContentHashType::SHA384:
                if(_stringHash.size() != 384/4)
                    throw InvalidContentHashException(_stringHash, _prefix, _postfix);
                break;
            case ContentHashType::SHA512:
                if(_stringHash.size() != 512/4)
                    throw InvalidContentHashException(_stringHash, _prefix, _postfix);
                break;
        }
    }

    void ContentHash::convertRawByteToStringHash()  {
        if(_rawByteHash != nullptr && _rawByteHash->_data != nullptr) {
            std::ostringstream outs;

            for (size_t i = 0; i < _rawByteHash->_size; i++)
                outs << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(_rawByteHash->_data[i]);

            _stringHash = outs.str();
        }
    }

    void ContentHash::trimPrefixFromStringHashInput() {
        boost::erase_all(_stringHash, _prefix);
    }

    void ContentHash::trimPostfixFromStringHashInput() {
        boost::erase_all(_stringHash, _postfix);
    }

}
