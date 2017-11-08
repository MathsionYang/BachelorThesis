#ifndef CONTENTSTANDARDIZATIONMODULE_REGEXSTANDARDIZATION_H
#define CONTENTSTANDARDIZATIONMODULE_REGEXSTANDARDIZATION_H

#include "INormalizationAlgorithm.h"
#include "RegexMatchReplacement.h"

#include <set>

namespace PDLS {

    class RegexNormalizationAlgorithm : public INormalizationAlgorithm {
        std::set<const RegexMatchReplacement*> _replacers;

    public:
        RegexNormalizationAlgorithm() {}
        virtual ~RegexNormalizationAlgorithm() {}

        RegexNormalizationAlgorithm(std::set<const RegexMatchReplacement*> m) : _replacers(m) {}
        RegexNormalizationAlgorithm(const RegexMatchReplacement* rM) { _replacers.insert(rM); }

        virtual NormalizedContent* normalizeContent(Content* dc) const override;

        const std::set<const RegexMatchReplacement*>& getMatchers() const {
            return _replacers;
        }

        void addReplacer(const RegexMatchReplacement& rM) {
            _replacers.insert(&rM);
        }

        void addReplacer(const RegexMatchReplacement* rM) {
            _replacers.insert(rM);
        }

    };

}

#endif //CONTENTSTANDARDIZATIONMODULE_REGEXSTANDARDIZATION_H
