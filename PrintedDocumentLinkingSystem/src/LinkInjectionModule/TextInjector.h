#ifndef PRINTEDDOCUMENTLINKINGSYSTEM_TEXTINJECTOR_H
#define PRINTEDDOCUMENTLINKINGSYSTEM_TEXTINJECTOR_H

#include "ILinkInjector.h"

namespace PDLS {

    class TextInjector : public ILinkInjector {
        bool _injectAtTail;
    public:
        TextInjector() : _injectAtTail(true) {}
        TextInjector(bool tail) : _injectAtTail(tail) {}
        virtual void injectLink(Document* txtDoc, Link* l, const bfs::path& out) throw(PDLSException) override;
    };

}


#endif //PRINTEDDOCUMENTLINKINGSYSTEM_TEXTINJECTOR_H
