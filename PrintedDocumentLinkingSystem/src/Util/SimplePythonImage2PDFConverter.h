#ifndef PRINTEDDOCUMENTLINKINGSYSTEM_PYTHONIMAGE2PDFCONVERTER_H
#define PRINTEDDOCUMENTLINKINGSYSTEM_PYTHONIMAGE2PDFCONVERTER_H

#include "IImage2PDFConverter.h"

namespace PDLS {
    class SimplePythonImage2PDFConverter : public IImage2PDFConverter {
        SimplePythonImage2PDFConverter() {}

    public:
        virtual Document* convertImage2PDF(Document* img) throw(PDLSException) override;

        static SimplePythonImage2PDFConverter* getInstance() {
            static SimplePythonImage2PDFConverter singleton;
            return &singleton;
        }

        SimplePythonImage2PDFConverter(const SimplePythonImage2PDFConverter&) = delete;
        void operator=(const  SimplePythonImage2PDFConverter&) = delete;
    };
}

#endif //PRINTEDDOCUMENTLINKINGSYSTEM_PYTHONIMAGE2PDFCONVERTER_H
