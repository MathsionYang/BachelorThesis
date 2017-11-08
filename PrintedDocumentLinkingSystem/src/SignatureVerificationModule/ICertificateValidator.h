#ifndef PRINTEDDOCUMENTVERIFICATIONSYSTEM_ICERTIFICATEVERIFICATIONSTRATEGY_H
#define PRINTEDDOCUMENTVERIFICATIONSYSTEM_ICERTIFICATEVERIFICATIONSTRATEGY_H

#include "../Datatypes/EnumTypes.h"
#include "../Datatypes/X509Certificate.h"

namespace PDLS {

    struct ICertificateValidator {
        virtual ValidationState validateCertificate(X509Certificate* x509) throw(PDLSException) = 0;
        virtual ~ICertificateValidator() { };
    };

}

#endif //PRINTEDDOCUMENTVERIFICATIONSYSTEM_ICERTIFICATEVERIFICATIONSTRATEGY_H
