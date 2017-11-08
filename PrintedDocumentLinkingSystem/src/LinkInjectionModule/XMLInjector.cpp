#include <pugixml.hpp>

#include "XMLInjector.h"
#include "../Datatypes/Link.h"

namespace PDLS {

    void XMLInjector::injectLink(Document* xmlDoc, Link* link, const bfs::path& out) throw(PDLSException) {
        if(xmlDoc == nullptr || link == nullptr)
            throw NullPointerException("XMLInjector::injectLink");
        if(xmlDoc->getType() != FileType::XML)
            throw StrategyMismatchException("XMLInjector::injectLink");

        //load xml from file stream
        pugi::xml_document xml;
        pugi::xml_parse_result res = xml.load(*(xmlDoc->getStream()));
        switch (res.status) {
            case pugi::status_ok:break;
            case pugi::status_file_not_found:
                throw LinkInjectionException("PugiXML internal File Loading Error! Cannot find file: " + xmlDoc->getPath().string());
            case pugi::status_no_document_element:
                throw LinkInjectionException("PugiXML internal File Loading Error! Document is not valid: " + xmlDoc->getPath().string());
            default:
                throw LinkInjectionException("PugiXML internal File Loading Error!");
        }

        //select the injection root node via xpath
        pugi::xml_node injectionRootNode = xml.select_node(_injectionRootElementXPath.c_str()).node();
        if(injectionRootNode.empty())
            throw LinkInjectionException("Cannot find root injection Node: " + _injectionRootElementXPath);

        pugi::xml_node* nodePtr = &injectionRootNode;

        for(auto n : _injectionElementNodeNames) {
            pugi::xml_node tmp = nodePtr->append_child(n.c_str());
            if(tmp.empty())
                throw LinkInjectionException("Cannot append child " + n );
            nodePtr = &tmp;
        }

        //inject link inside fo:inline as pc data
        if(!nodePtr->append_child(pugi::node_pcdata).set_value(link->getInjectionString().c_str()))
            throw PDLSException(); //injection exception

        //save to disk
        if(!xml.save_file(out.c_str()))
            throw SavingFileException(out);
    }
}


