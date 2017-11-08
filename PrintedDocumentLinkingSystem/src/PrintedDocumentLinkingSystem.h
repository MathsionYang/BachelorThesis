#ifndef PRINTEDDOCUMENTLINKINGSYSTEM_PDVS_H
#define PRINTEDDOCUMENTLINKINGSYSTEM_PDVS_H

#include "ContentExtractionModule/ContentExtractionModule.h"
#include "ContentNormalizationModule/ContentNormalizationModule.h"
#include "ContentHashGenerationModule/ContentHashGenerationModule.h"
#include "SignatureGenerationModule/SignatureGenerationModule.h"
#include "DocumentLinkingModule/DocumentLinkingModule.h"
#include "LinkInjectionModule/LinkInjectionModule.h"
#include "ContentValidationModule/ContentValidationModule.h"
#include "SignatureVerificationModule/SignatureVerificationModule.h"
#include "LinkExtractionModule/LinkExtractionModule.h"
#include "LDataLoadingModule/LDataLoadingModule.h"
#include "boost/program_options.hpp"

namespace PDLS {

    namespace bpo = boost::program_options;

    class PrintedDocumentLinkingSystem final {

        //flag that indicates that the input PDF doc is a PDF that contains textual (and searchable) content
        bool _isTextPDF;
        bool _noLIM;
        bool _noLEM;
        bool _saveConvertedFile;

        //modules
        ContentExtractionModule* _cem;
        ContentNormalizationModule* _csm;
        ContentHashGenerationModule* _chgm;
        SignatureGenerationModule* _sgm;
        DocumentLinkingModule* _drm;
        LinkInjectionModule* _lim;
        LinkExtractionModule* _lem;
        LDataLoadingModule* _ldlm;
        ContentValidationModule* _cvm;
        SignatureVerificationModule* _svm;

        //content hash info
        ContentHashType _contentHashType;
        std::string _contentHashPrefix;
        std::string _contentHashPostfix;

        //boost cli program options
        bpo::options_description _programOptionDescription;

        PrintedDocumentLinkingSystem() : _cem(ContentExtractionModule::getInstance()),
                                         _csm(ContentNormalizationModule::getInstance()),
                                         _chgm(ContentHashGenerationModule::getInstance()),
                                         _sgm(SignatureGenerationModule::getInstance()),
                                         _drm(DocumentLinkingModule::getInstance()),
                                         _lim(LinkInjectionModule::getInstance()),
                                         _lem(LinkExtractionModule::getInstance()),
                                         _ldlm(LDataLoadingModule::getInstance()),
                                         _cvm(ContentValidationModule::getInstance()),
                                         _svm(SignatureVerificationModule::getInstance()),
                                         _programOptionDescription("Program Options"),
                                         _isTextPDF(false),
                                         _noLIM(false),
                                         _noLEM(false),
                                         _saveConvertedFile(false)  { initProgramOptions(); }

        void initProgramOptions();

        int linkDocument(Document* doc, RSAPrivateKey* pK, X509Certificate* cert, const bfs::path& outputDocPath) throw(PDLSException);
        int verifyDocument(Document* doc, LinkDescription* desc) throw(PDLSException);
        std::string readStringFromTerminal(const std::string& prompt);
        void printDocumentVerificationState(DocumentVerificationState state);

        DocumentVerificationState evaluateDocumentVerificationState(ValidationState state,
                                                                    SignatureVerificationState verificationState);
    public:

        int run(int argc, char** argv);
        static PrintedDocumentLinkingSystem* getInstance() {
            static PrintedDocumentLinkingSystem singleton;
            return &singleton;
        }

        bool inputIsTextPDF() const {
            return _isTextPDF;
        }

        bool isNoLIM() const {
            return _noLIM;
        }

        bool isNoLEM() const {
            return _noLEM;
        }

        bool saveConvertedFile() const {
            return _saveConvertedFile;
        }

        PrintedDocumentLinkingSystem(const PrintedDocumentLinkingSystem&) = delete;

        void operator=(const PrintedDocumentLinkingSystem&) = delete;

    };

}

#endif //PRINTEDDOCUMENTLINKINGSYSTEM_PDVS_H
