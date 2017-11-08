#ifndef PRINTEDDOCUMENTVERIFICATIONSYSTEM_REGEXLDataLINKEXTRACTOR_H
#define PRINTEDDOCUMENTVERIFICATIONSYSTEM_REGEXLDataLINKEXTRACTOR_H

#include "ILinkExtractor.h"
#include "../Datatypes/Content.h"
#include "../Datatypes/Link.h"
#include "../Datatypes/LinkDescription.h"

namespace PDLS {

    class TextLinkExtractor : public ILinkExtractor {
        Content* extractDocumentContent(Document* doc);
        boost::regex&& createLinkMatcher(LinkDescription* desc);
    public:
        virtual Link* extractLink(Document* doc, LinkDescription* desc) throw(PDLSException) override;
    };

}
#endif //PRINTEDDOCUMENTVERIFICATIONSYSTEM_REGEXLDataLINKEXTRACTOR_H
