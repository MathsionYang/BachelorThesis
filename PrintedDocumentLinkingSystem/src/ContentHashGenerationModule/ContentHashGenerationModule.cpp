#include "ContentHashGenerationModule.h"

namespace PDLS {


    ContentHash* ContentHashGenerationModule::generateContentHash(NormalizedContent* sdc, ContentHashType hT, const std::string& hashPrefix, const std::string& hashPostfix) throw(PDLSException) {
        if(_hashGenerator == nullptr) _hashGenerator = new OpenSSLContentHashGenerator(hT, hashPrefix, hashPostfix);
        return _hashGenerator->generateContentHash(sdc);
    }

    ContentHash* ContentHashGenerationModule::generateContentHash(NormalizedContent* sdc) throw(PDLSException) {
        if(_hashGenerator == nullptr) _hashGenerator = new OpenSSLContentHashGenerator();
        return _hashGenerator->generateContentHash(sdc);
    }

}
