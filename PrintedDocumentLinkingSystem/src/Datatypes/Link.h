#ifndef PRINTEDDOCUMENTLINKINGSYSTEM_LINK_H
#define PRINTEDDOCUMENTLINKINGSYSTEM_LINK_H

#include <nlohmann/json.hpp>
#include <boost/algorithm/string.hpp>
#include "ContentHash.h"
#include "RSAKey.h"
#include "Document.h"
#include "../Util/IProvider.h"

namespace PDLS {

    class Link {
        std::string _value;
        LinkDescription* _linkDescription;

    public:
        static const std::string __PREFIX__;
        static const std::string __POSTFIX__;

        Link(const std::string& value, LinkDescription* desc) : _value(value), _linkDescription(desc) {
            //remove prefix & postfix from link
            boost::erase_all(_value, __PREFIX__);
            boost::erase_all(_value, __POSTFIX__);
            _linkDescription->eval(_value);
        }

        inline const std::string& getLinkAsString() const {
            return _value;
        }

        LinkDescription* getLinkDescription() const {
            return _linkDescription;
        }

        //produces the text that gets injected into documents
        const std::string getInjectionString();
    };
}

#endif //PRINTEDDOCUMENTLINKINGSYSTEM_LINK_H
