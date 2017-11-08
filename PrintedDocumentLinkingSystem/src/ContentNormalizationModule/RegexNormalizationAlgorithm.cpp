#include "RegexNormalizationAlgorithm.h"

#include <boost/regex.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <iostream>

namespace PDLS {

    NormalizedContent* RegexNormalizationAlgorithm::normalizeContent(Content* dc) const {
        std::string* res = new std::string(dc->getValue());

        for(const RegexMatchReplacement* rm : _replacers) {
            boost::regex expression(rm->getMatcher());
            *res = boost::regex_replace(*res, expression, rm->getReplacement(), boost::match_default | boost::format_all);
        }

        boost::algorithm::trim(*res);

        return new NormalizedContent(dc->getOwner(), dc, *res);
    }

}
