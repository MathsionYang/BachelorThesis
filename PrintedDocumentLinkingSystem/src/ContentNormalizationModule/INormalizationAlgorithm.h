#ifndef CONTENTSTANDARDIZATIONMODULE_STANDARDIZATIONSTRATEGY_H
#define CONTENTSTANDARDIZATIONMODULE_STANDARDIZATIONSTRATEGY_H

#include "../Datatypes/NormalizedContent.h"

namespace PDLS {

    struct INormalizationAlgorithm {
        virtual NormalizedContent* normalizeContent(Content* dc) const = 0;
        virtual ~INormalizationAlgorithm() {}
    };

}

#endif //CONTENTSTANDARDIZATIONMODULE_STANDARDIZATIONSTRATEGY_H
