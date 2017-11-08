#ifndef CONTENTHASHGENERATIONMODULE_CONTENTHASHGENERATIONMODULE_H
#define CONTENTHASHGENERATIONMODULE_CONTENTHASHGENERATIONMODULE_H

#include <boost/filesystem.hpp>
#include <set>
#include <iostream>

#include "OpenSSLContentHashGenerator.h"
#include "../Datatypes/NormalizedContent.h"
#include "../Datatypes/PDLSException.h"
#include "../Datatypes/EnumTypes.h"

namespace PDLS {

    class ContentHashGenerationModule {
        IContentHashGenerator* _hashGenerator;

        ContentHashGenerationModule() : _hashGenerator(nullptr) { }

        ContentHash* generateContentHash(NormalizedContent* sdc) throw(PDLSException);
    public:

        static ContentHashGenerationModule* getInstance() {
            static ContentHashGenerationModule singleton;
            return &singleton;
        }

        ContentHash* generateContentHash(NormalizedContent* sdc, ContentHashType hT, const std::string& hashPrefix, const std::string& hashPostfix) throw(PDLSException);

        inline IContentHashGenerator* getHashGenerator() const {
            return _hashGenerator;
        }

        inline void setHashGenerator(OpenSSLContentHashGenerator* hashGenerator) {
            _hashGenerator = hashGenerator;
        }

        ContentHashGenerationModule(const ContentHashGenerationModule&) = delete;
        void operator=(const ContentHashGenerationModule&) = delete;

    };

}

#endif //CONTENTHASHGENERATIONMODULE_CONTENTHASHGENERATIONMODULE_H
