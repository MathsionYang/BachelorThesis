#ifndef CONTENTSTANDARDIZATIONMODULE_CONTENTSTANDARDIZATIONMODULE_H
#define CONTENTSTANDARDIZATIONMODULE_CONTENTSTANDARDIZATIONMODULE_H

#include <boost/filesystem.hpp>
#include <string>
#include <set>
#include <iostream>

#include "INormalizationAlgorithm.h"
#include "../Datatypes/Content.h"
#include "../Datatypes/PDLSException.h"

namespace PDLS {

    class ContentNormalizationModule {
        INormalizationAlgorithm* _strategy;
        ContentNormalizationModule();

    public:
        NormalizedContent* normalizeContent(Content* dc) throw(PDLSException);

        INormalizationAlgorithm* createDefaultStrategy();

        static ContentNormalizationModule* getInstance() {
            static ContentNormalizationModule singleton;
            return &singleton;
        }

        inline INormalizationAlgorithm* getStrategy() const {
            return _strategy;
        }

        inline void setStrategy(INormalizationAlgorithm* strategy) {
            _strategy = strategy;
        }

        ContentNormalizationModule(const ContentNormalizationModule&) = delete;
        void operator=(const ContentNormalizationModule&) = delete;
    };

}

#endif //CONTENTSTANDARDIZATIONMODULE_CONTENTSTANDARDIZATIONMODULE_H
