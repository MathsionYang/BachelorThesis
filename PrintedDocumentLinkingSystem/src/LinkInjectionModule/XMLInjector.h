#ifndef PRINTEDDOCUMENTVERIFICATIONSYSTEM_XSLFOLDataLINKINJECTOR_H
#define PRINTEDDOCUMENTVERIFICATIONSYSTEM_XSLFOLDataLINKINJECTOR_H

#include <pugixml.hpp>
#include "ILinkInjector.h"
#include "../Datatypes/LinkingData.h"
#include "../Datatypes/Link.h"

namespace PDLS {

    class XMLInjector : public ILinkInjector {
        std::string _injectionRootElementXPath;
        std::list<std::string> _injectionElementNodeNames;

    public:

        XMLInjector(const std::string& rootXpath, const std::list<std::string>& injectionNode) : _injectionRootElementXPath(rootXpath), _injectionElementNodeNames(injectionNode) {}

        virtual void injectLink(Document* xmlDoc, Link* link, const bfs::path& out) throw(PDLSException) override;

        const std::string& getInjectionRootElementXPath() const {
            return _injectionRootElementXPath;
        }

        void setInjectionRootElementXPath(const std::string& injectionRootElementXPath) {
            _injectionRootElementXPath = injectionRootElementXPath;
        }

        const std::list<std::string>& getInjectionElementNodeNames() const {
            return _injectionElementNodeNames;
        }

        void setInjectionElementNodeNames(const std::list<std::string>& injectionElementNodeNames) {
            _injectionElementNodeNames = injectionElementNodeNames;
        }
    };
}

#endif //PRINTEDDOCUMENTVERIFICATIONSYSTEM_XSLFOLDataLINKINJECTOR_H
