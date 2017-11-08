#ifndef PRINTEDDOCUMENTLINKINGSYSTEM_LINKDESCRIPTION_H
#define PRINTEDDOCUMENTLINKINGSYSTEM_LINKDESCRIPTION_H

#include "PDLSException.h"
#include <string>
#include <boost/regex.hpp>

namespace PDLS {
//class to describe what a link of a specific provider looks like
    class LinkDescription {
        std::string _providerID;
        std::string _regexMatcher;
    public:
        LinkDescription(const std::string& id,
                        const std::string& matcher) : _providerID(id),
                                                      _regexMatcher(matcher) { }

        const std::string& getProviderID() const {
            return _providerID;
        }

        const std::string& getRegexMatcher() const {
            return _regexMatcher;
        }

        inline void eval(const std::string& linkValue) throw(PDLSException) {
            if (!boost::regex_match(linkValue, boost::regex(_regexMatcher)))
                throw LinkDescriptionMismatchException(linkValue, _providerID, _regexMatcher);
        }

        bool operator==(const LinkDescription& rhs) {
            return (rhs._providerID == _providerID) && (rhs._regexMatcher == _regexMatcher);
        }

        bool operator!=(const LinkDescription& rhs) { return !operator==(rhs); }
    };
}

#include <boost/regex.hpp>

#endif //PRINTEDDOCUMENTLINKINGSYSTEM_LINKDESCRIPTION_H
