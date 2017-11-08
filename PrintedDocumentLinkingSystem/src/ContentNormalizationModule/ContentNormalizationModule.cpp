#include <fstream>
#include <sstream>
#include <string>

#include <boost/algorithm/string/trim.hpp>

#include "ContentNormalizationModule.h"
#include "RegexNormalizationAlgorithm.h"

namespace PDLS {

    ContentNormalizationModule::ContentNormalizationModule() : _strategy(nullptr) { _strategy = createDefaultStrategy(); }

    NormalizedContent* ContentNormalizationModule::normalizeContent(Content* dc) throw(PDLSException) {
        if(_strategy == nullptr) {
            throw NoStrategyException("CSM");
        }
        return _strategy->normalizeContent(dc);
    }

    INormalizationAlgorithm* ContentNormalizationModule::createDefaultStrategy() {
        RegexNormalizationAlgorithm* regexStrategy = new RegexNormalizationAlgorithm;

        //matches any non-word character (or any character not inside []
        RegexMatchReplacement* nonWordCharReplacer = new RegexMatchReplacement("\\s", "\\n");//new RegexMatchReplacement("[^a-zA-Z0-9üÜäAöÖß_\\-,.#~+*?!&%$'§[(){}'`;<>|\\/\\]]", "\\n");
        regexStrategy->addReplacer(nonWordCharReplacer);

        //matches multiple newlines (emptylines)
        RegexMatchReplacement* multipleNewlineReplacer = new RegexMatchReplacement("(\\s*\\n){2,}", "\\n");
        regexStrategy->addReplacer(multipleNewlineReplacer);

        return regexStrategy;
    }


}
