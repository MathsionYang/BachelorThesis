#include "XMLExtractor.h"

#include "../../Datatypes/Content.h"

#include <pugixml.hpp>

namespace PDLS {

    Content* XMLExtractor::extractContent(Document* xmlDoc)throw(PDLSException) {

        pugi::xml_document doc;
        doc.load(*xmlDoc->getStream());

        std::stringstream res;

        for(auto n : doc.select_nodes(_contentElementNodeXPath.c_str())) {
            res << n.node().child_value() << std::endl;
        }

        return new Content(xmlDoc, res.str());
    }

}
