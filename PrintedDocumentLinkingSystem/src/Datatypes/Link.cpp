#include "Link.h"

#include <boost/algorithm/string.hpp>

namespace PDLS {
    //static member initialization
    const std::string Link::__POSTFIX__ = "###";
    const std::string Link::__PREFIX__ = "###";

    const std::string Link::getInjectionString() {
        std::stringstream ss;
        ss << __PREFIX__ << _value << __POSTFIX__;
        return ss.str();
    }
}