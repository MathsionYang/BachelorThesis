#ifndef PRINTEDDOCUMENTVERIFICATIONSYSTEM_CONTENTVALIDATIONMODULE_H
#define PRINTEDDOCUMENTVERIFICATIONSYSTEM_CONTENTVALIDATIONMODULE_H

#include "../Datatypes/Document.h"
#include "../Datatypes/EnumTypes.h"
#include "../Datatypes/ContentHash.h"
#include "../Datatypes/PDLSException.h"

#include <iostream>

namespace PDLS {


    class ContentValidationModule {

        //ContentHash* generateValidationContentHash(Document* inDoc, ContentHashType hT, const std::string& prefix, const std::string& postfix) const throw(PDLSException);

        ContentValidationModule() {}

    public:
        static ContentValidationModule* getInstance() {
            static ContentValidationModule singleton;
            return &singleton;
        }

        //ValidationState validateContent(Document* doc, ContentHash* chash) throw(PDLSException);
            ValidationState validateContent(ContentHash* chashA, ContentHash* chashB) throw(PDLSException);

        ContentValidationModule(const ContentValidationModule&) = delete;
        void operator=(const ContentValidationModule&) = delete;
    };

}

#endif //PRINTEDDOCUMENTVERIFICATIONSYSTEM_CONTENTVALIDATIONMODULE_H
