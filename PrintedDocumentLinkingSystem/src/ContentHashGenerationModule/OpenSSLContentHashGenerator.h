#ifndef CONTENTHASHGENERATIONMODULE_HASHGENERATIONSTRATEGY_H
#define CONTENTHASHGENERATIONMODULE_HASHGENERATIONSTRATEGY_H

#include <string>

#include "IContentHashGenerator.h"
#include "../Datatypes/EnumTypes.h"

namespace PDLS {

    class OpenSSLContentHashGenerator : public IContentHashGenerator {
        ContentHashType _hashType;
        std::string _hashPrefix;
        std::string _hashPostfix;

    public:
        OpenSSLContentHashGenerator(ContentHashType hT, const std::string& pre, const std::string& pos) : _hashType(hT), _hashPrefix(pre), _hashPostfix(pos) {}
        OpenSSLContentHashGenerator() : _hashType(ContentHashType::SHA256), _hashPrefix("#HSU#"), _hashPostfix("CH") {}

        ContentHash* generateContentHash(NormalizedContent* sdc) throw(PDLSException) override;

        ContentHashType getHashType() const {
            return _hashType;
        }

        void setHashType(ContentHashType hashType) {
            _hashType = hashType;
        }

        const std::string& getHashPrefix() const {
            return _hashPrefix;
        }

        void setHashPrefix(const std::string& hashPrefix) {
            _hashPrefix = hashPrefix;
        }

        const std::string& getHashPostfix() const {
            return _hashPostfix;
        }

        void setHashPostfix(const std::string& hashPostfix) {
            _hashPostfix = hashPostfix;
        }
    };

}

#endif //CONTENTHASHGENERATIONMODULE_HASHGENERATIONSTRATEGY_H
