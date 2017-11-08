#ifndef CONTENTSTANDARDIZATIONMODULE_REGEXMATCHER_H
#define CONTENTSTANDARDIZATIONMODULE_REGEXMATCHER_H

#include <string>

namespace PDLS {

    class RegexMatchReplacement {
        std::string _matcher;
        std::string _replacement;

    public:

        RegexMatchReplacement(const std::string& m, const std::string& r) : _matcher(m), _replacement(r) {}

        const std::string& getMatcher() const {
            return _matcher;
        }

        void setMatcher(const std::string& matcher) {
            _matcher = matcher;
        }

        const std::string& getReplacement() const {
            return _replacement;
        }

        void setReplacement(const std::string& replacement) {
            _replacement = replacement;
        }

    };

}

#endif //CONTENTSTANDARDIZATIONMODULE_REGEXMATCHER_H
