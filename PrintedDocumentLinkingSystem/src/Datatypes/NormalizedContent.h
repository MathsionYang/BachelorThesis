#ifndef PRINTEDDOCUMENTVERIFICATIONSYSTEM_STANDARDIZEDDOCUMENTCONTENT_H
#define PRINTEDDOCUMENTVERIFICATIONSYSTEM_STANDARDIZEDDOCUMENTCONTENT_H

#include "Content.h"

namespace PDLS {

    class NormalizedContent : public Content  {
        const Content* _original;
    public:

        NormalizedContent(Document* owner, const Content* original, const std::string& stdized) : Content(owner, stdized), _original(original) { }
        const Content* getOriginal() const {
            return _original;
        }

        void setOriginal(const Content* original) {
            _original = original;
        }
    };

}

#endif //PRINTEDDOCUMENTVERIFICATIONSYSTEM_STANDARDIZEDDOCUMENTCONTENT_H
