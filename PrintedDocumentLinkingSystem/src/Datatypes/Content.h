#ifndef PRINTEDDOCUMENTVERIFICATIONSYSTEM_DOCUMENTCONTENT_H
#define PRINTEDDOCUMENTVERIFICATIONSYSTEM_DOCUMENTCONTENT_H

#include "Document.h"

namespace PDLS {

    class Content {
    protected:
        Document* _owner;
        std::string _value;

    public:

        Content(Document* ownr, const std::string& cntnt) : _owner(ownr), _value(cntnt) {}
        Content(Document* ownr, std::string& cntnt) : _owner(ownr), _value(cntnt) {}
        Content(Document* ownr, const std::string&& cntnt) : _owner(ownr), _value(cntnt) {}
        Content(Document* ownr, std::string&& cntnt) : _owner(ownr), _value(cntnt) {}

        Document* getOwner() const {
            return _owner;
        }

        const std::string& getValue() const {
            return _value;
        }

        void setValue(const std::string& value) {
            _value = value;
        }
    };

}

#endif //PRINTEDDOCUMENTVERIFICATIONSYSTEM_DOCUMENTCONTENT_H
