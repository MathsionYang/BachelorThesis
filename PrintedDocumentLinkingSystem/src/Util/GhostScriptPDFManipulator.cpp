#include "GhostScriptPDFManipulator.h"
#include <sstream>

namespace PDLS {
    
    Document* GhostScriptPDFManipulator::convertPDF2Image(Document* pdfDoc, int dpi) throw(PDLSException) {
        std::cout << std::endl << "Starting GhostScript Converter to convert '" << pdfDoc->getPath() << "' to an Image-File..." << std::endl << std::endl;
        std::stringstream gsCommand;
        gsCommand << "-pdf2png -dNOPAUSE -dBATCH -dSAFER -dQUITE -sDEVICE=png16m -dDOINTERPOLATE -r"<< dpi <<" -sOutputFile=" << pdfDoc->getPath().c_str() << ".png " << pdfDoc->getPath().string();
        auto gsCmdArgs = generateGhostScriptCommandArguments(gsCommand.str());

        executeGhostScriptCommand(gsCmdArgs);
        std::cout << std::endl << "...Done!'" << std::endl << std::endl;

        return new Document(bfs::path(pdfDoc->getPath().string() + ".png"));
    }

    Document* GhostScriptPDFManipulator::convertPDF2Text(Document* pdfDoc) throw(PDLSException) {
        std::cout << std::endl << "Starting GhostScript Converter to convert '" << pdfDoc->getPath() << "' to a Text-File..." << std::endl << std::endl;

        std::stringstream gsCommand;
        gsCommand << "-pdf2txt -dNOPAUSE -dBATCH -dSAFER -dQUITE -sDEVICE=txtwrite -sOutputFile="  << pdfDoc->getPath().c_str() << ".txt " << pdfDoc->getPath().string();
        auto gsCmdArgs = generateGhostScriptCommandArguments(gsCommand.str());

        executeGhostScriptCommand(gsCmdArgs);

        std::cout << std::endl << "...Done!'" << std::endl << std::endl;
        return new Document(bfs::path(pdfDoc->getPath().string() + ".txt"));
    }

    std::shared_ptr<std::vector<std::string>> GhostScriptPDFManipulator::generateGhostScriptCommandArguments(
            const std::string& gsCMD) {
        std::stringstream ss(gsCMD);
        std::string argToken;

        auto argVector = std::make_shared<std::vector<std::string>>();

        while(std::getline(ss, argToken, ' ')) {
            argVector->push_back(argToken);
        }

        return argVector;
    }

    void GhostScriptPDFManipulator::executeGhostScriptCommand(std::shared_ptr<std::vector<std::string>> gsCmdArgs) throw(PDLSException) {
        int gsRetCode = 0;
        void* gsInstance;

        //create new GS api
        gsRetCode = gsapi_new_instance(&gsInstance, NULL);

        if(gsRetCode < gs_error_ok)
            throw GhostScriptInitializationException();
        //set api encoding to utf8
        gsRetCode = gsapi_set_arg_encoding(gsInstance, GS_ARG_ENCODING_UTF8);

        if(gsRetCode == gs_error_ok) {
            //create the c style array containing the c style string parameters for gs command
            const char* gsArgv[gsCmdArgs->size()];
            unsigned j = 0;
            for(auto i = gsCmdArgs->begin(), e = gsCmdArgs->end(); i!=e; i++, j++)
                gsArgv[j] = i->c_str();

            //init gsapi with gs command parameters
            gsRetCode = gsapi_init_with_args(gsInstance, (int)gsCmdArgs->size(), const_cast<char**>(gsArgv));

            if(gsRetCode != gs_error_ok)
                throw GhostScriptInitializationException();

            //exit api
            gsapi_exit(gsInstance);

        } else
            throw GhostScriptInitializationException();

        //free api from memory
        gsapi_delete_instance(gsInstance);
    }


}
