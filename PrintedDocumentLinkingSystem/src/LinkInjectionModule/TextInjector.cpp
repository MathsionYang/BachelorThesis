#include "TextInjector.h"
#include "../Datatypes/Content.h"

namespace PDLS {
    void TextInjector::injectLink(Document* txtDoc, Link* l, const bfs::path& out) throw(PDLSException) {
        if(txtDoc == nullptr || link == nullptr)
            throw NullPointerException("XMLInjector::injectLink");
        if(txtDoc->getType() != FileType::TXT)
            throw StrategyMismatchException("TextInjector::injectLink");

        std::ofstream output (out.string());
        if (output.is_open()) {
            if(!_injectAtTail)
                output << l->getLinkAsString() << std::endl;
            output << txtDoc->getContent()->getValue() << std::endl;
            if(_injectAtTail)
                output << l->getLinkAsString() << std::endl;
            output.close();
        } else
            throw SavingFileException(out);
    }

}


