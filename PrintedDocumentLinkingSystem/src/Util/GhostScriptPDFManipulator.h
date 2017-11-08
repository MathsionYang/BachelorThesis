#ifndef PRINTEDDOCUMENTVERIFICATIONSYSTEM_GHOSTSCRIPTPDFMANIPULATOR_H
#define PRINTEDDOCUMENTVERIFICATIONSYSTEM_GHOSTSCRIPTPDFMANIPULATOR_H

#include <vector>
#include <string>

#include <ghostscript/iapi.h>
#include <ghostscript/ierrors.h>

#include "IPDF2ImageConverter.h"
#include "IPDF2TextConverter.h"

namespace PDLS {

    class GhostScriptPDFManipulator : public IPDF2ImageConverter, public IPDF2TextConverter {

        //see http://www.ghostscript.com/doc/current/Use.htm#Options
        std::shared_ptr<std::vector<std::string>> generateGhostScriptCommandArguments(const std::string& gsCMD);

        void executeGhostScriptCommand(std::shared_ptr<std::vector<std::string>> gsCmdArgs) throw(PDLSException);

        GhostScriptPDFManipulator() {}


    public:

        static GhostScriptPDFManipulator* getInstance() {
            static GhostScriptPDFManipulator singleton;
            return &singleton;
        }

        virtual Document* convertPDF2Image(Document* pdf, int dpi) throw(PDLSException) override;

        virtual Document* convertPDF2Text(Document* pdf) throw(PDLSException) override;

        GhostScriptPDFManipulator(const GhostScriptPDFManipulator&) = delete;
        void operator=(const GhostScriptPDFManipulator&) = delete;
    };

}

#endif //PRINTEDDOCUMENTVERIFICATIONSYSTEM_GHOSTSCRIPTPDFMANIPULATOR_H
