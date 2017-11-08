#include "PrintedDocumentLinkingSystem.h"

namespace PDLS {


    int PrintedDocumentLinkingSystem::linkDocument(Document* doc, RSAPrivateKey* pK,
                                                   X509Certificate* cert, const bfs::path& outputDocPath) throw(PDLSException) {

        try {
            //extract document content
            _cem->treatInputPDFAsTextPDF(_isTextPDF);
            Content* dc = _cem->extractContent(doc);
            doc->setContent(dc);

            //standardize document content
            NormalizedContent* sdc = _csm->normalizeContent(dc);
            doc->setNormalizedContent(sdc);

            //set content hash pre- and postfix to default values if not set by user
            if(_contentHashPrefix.size() == 0)
                _contentHashPrefix = "#HSU#";
            if(_contentHashPostfix.size() == 0)
                _contentHashPostfix = "#CH#";

            //generate content hash
            ContentHash* ch = _chgm->generateContentHash(sdc, _contentHashType, _contentHashPrefix, _contentHashPostfix);
            doc->setContentHash(ch);

            //generate signature
            Signature* sig = _sgm->generateSignature(ch, pK);
            doc->setSignature(sig);

            //link the document to ipfs
            Link* link = _drm->linkDocument(doc, cert);

            if(_noLIM)
                std::cout << "Successfully linked document with Link: " << link->getInjectionString();
            else {
                //inject link into document and produce output document
                _lim->setSaveConvertedDocument(_saveConvertedFile);
                _lim->injectLink(doc, link, outputDocPath);

                std::cout << "Successfully linked document and created verifiable document: " << outputDocPath << std::endl;
            }

            return 0;

        } catch (PDLSException& e) {
            std::cerr << e.what();
            return -1;
        } catch (...) {
            std::cerr << "FATAL ERROR: Unexpected Exception!";
            return -2;
        }
    }

    int PrintedDocumentLinkingSystem::verifyDocument(Document* doc, LinkDescription* desc) throw(PDLSException) {

        try {
            _cem->treatInputPDFAsTextPDF(_isTextPDF);
            Content* dc = _cem->extractContent(doc);
            doc->setContent(dc);

            Link* link = nullptr;
            if(_noLEM) {
                std::string linkString = readStringFromTerminal("Please insert Link of Document: ");

                link = new Link(linkString, desc);
            } else {
                //extract the Link of the document
                _lem->setSaveConvertedFile(_saveConvertedFile);
                link = _lem->extractLink(doc, desc);
                doc->setLink(link);
            }

            //download LData
            LinkingData* ldata = _ldlm->loadLinkingData(link);

            //Standardize doc content
            NormalizedContent* sdc = _csm->normalizeContent(dc);
            doc->setNormalizedContent(sdc);

            //get content hash from LData
            ContentHash* ldataContentHash = ldata->getContentHash();

            //generate compare content hash of document
            ContentHash* compareContentHash = _chgm->generateContentHash(sdc,
                                                                            ldataContentHash->getType(),
                                                                            ldataContentHash->getPrefix(),
                                                                            ldataContentHash->getPostfix());

            //validate the content of the document with the two hashes
            ValidationState cvs = _cvm->validateContent(ldataContentHash, compareContentHash);

            //validate signature with cert
            SignatureVerificationState svs = _svm->verifySignature(ldataContentHash, ldata->getSignature(),
                                                                   ldata->getCertificate());

            DocumentVerificationState dvs = evaluateDocumentVerificationState(cvs, svs);

            //print document verification state
	    std::cout << "Validationstate of Document '" << doc->getPath().string()  << "' is : ";
	    printDocumentVerificationState(dvs);

            return 0;

        } catch (PDLSException& e) {
            std::cerr << e.what();
            return -1;
        } catch (...) {
            std::cerr << "FATAL ERROR: Unexpected Exception!";
            return -2;
        }
    }

    void PrintedDocumentLinkingSystem::initProgramOptions() {
        _programOptionDescription.add_options()
                ("help,h", "Print this help Message")
                ("link,l", "Create a verifiable document")
                ("verify,v", "Verify a document")
                ("document,d", bpo::value<std::string>(), "/path/to/document")
                ("privateKey,k", bpo::value<std::string>(), "/path/to/rsa/privateKey.pem")
                ("x509-certificate,c", bpo::value<std::string>(), "/path/to/x509/certificate.pem")
                ("provider,p", bpo::value<std::string>(), "Provider where the Document should be linked or where it is linked (only IPFS is supported right now so this option can be ignored for now)")
                ("output,o", bpo::value<std::string>(), "/path/to/output/doc")
                ("chType,t", bpo::value<std::string>(), "Content Hash Type (MD5 | SHA1 | SHA224 | SHA256 | SHA384 | SHA512)")
                ("chPrefix", bpo::value<std::string>(&_contentHashPrefix), "Content Hash Prefix, Default : #HSU#")
                ("chPostfix", bpo::value<std::string>(&_contentHashPostfix), "Content Hash Postfix, Default : #CH#")
                ("textPDF", "Flag that indicates that the input PDF doc is a PDF that contains textual (and searchable) content")
                ("noLIM", "Don't run Link-Injection-Module -> Link gets printed in Terminal and is not injected into Document!")
                ("noLEM", "Don't run Link-Extraction-Module -> User has to provide the Link via Terminal!")
                ("saveConvertedFile", "If the input document is a PDF it gets converted. If this option is set, the converted file gets saved in the directory of the input document!");

    }

    int PrintedDocumentLinkingSystem::run(int argc, char** argv) {
        if(argc == 1) {
            std::cout << _programOptionDescription;
            return -1;
        }

        bpo::variables_map vm;
        try {
            bpo::store(bpo::parse_command_line(argc, argv, _programOptionDescription), vm); // can throw

            if(vm.count("help")) {
                std::cout << _programOptionDescription;
                return 0;
            }

            //check flags
            _isTextPDF = vm.count("textPDF") >= 1;
            _noLIM = vm.count("noLIM") >= 1;
            _noLEM = vm.count("noLEM") >= 1;
            _saveConvertedFile = vm.count("saveConvertedFile") >= 1;

            bpo::notify(vm); // throws on error -> to check for any falsely set program options

        } catch (bpo::error& e) {
            std::cerr << "ERROR: " << e.what() << std::endl << std::endl;
            std::cerr << _programOptionDescription << std::endl;
        }

        if(vm.count("link")) {
            Document* doc = nullptr;
            RSAPrivateKey* prK = nullptr;
            X509Certificate* cert = nullptr;
            std::string out("");

            if (vm.count("document"))
                //create and load doc
                doc = new Document(vm["document"].as<std::string>());
            else
                doc = new Document(readStringFromTerminal("Path to Input Document"));

            if (vm.count("privateKey"))
                //create and load priv key from pem file
                prK = new RSAPrivateKey(new File(vm["privateKey"].as<std::string>()));
            else
                prK = new RSAPrivateKey(new File(bfs::path(readStringFromTerminal("Path to PrivateKey PEM File"))));

            if (vm.count("x509-certificate"))
                //clreate and load self signed x509 cert from pem file
                cert = new X509Certificate(new File(vm["x509-certificate"].as<std::string>()), true);
            else
                cert = new X509Certificate(new File(bfs::path(readStringFromTerminal("Path to X.509 Certificate"))), true);

            if (vm.count("output"))
                //get output file path string
                out = vm["output"].as<std::string>();
            else
                out = readStringFromTerminal("Path to save Output Document");

            if (vm.count("chType"))
                _contentHashType = ContentHash::getTypeFromString(vm["chType"].as<std::string>());
            else
                _contentHashType = ContentHashType::SHA256;

            return linkDocument(doc, prK, cert, out);
        } else if(vm.count("verify")) {
            Document* doc = nullptr;

            if (vm.count("document"))
                //create and load doc
                doc = new Document(vm["document"].as<std::string>());
            else
                doc = new Document(readStringFromTerminal("Path to Input Document"));

            return verifyDocument(doc, IPFSProvider::getInstance()->getSupportedLinkDescription());
        } else {
            std::cout << _programOptionDescription;
        }
    }

    DocumentVerificationState PrintedDocumentLinkingSystem::evaluateDocumentVerificationState(
            ValidationState contentValidationState, SignatureVerificationState signatureVerificationState) {
        switch (contentValidationState) {
            case ValidationState::VALID:
                switch (signatureVerificationState) {
                    case SignatureVerificationState::CERT_VALID_SIG_VALID:
                        return DocumentVerificationState::CONTENT_VALID_CERT_VALID_SIG_VALID;
                    case SignatureVerificationState::CERT_INVALID_SIG_VALID:
                        return DocumentVerificationState::CONTENT_VALID_CERT_INVALID_SIG_VALID;
                    case SignatureVerificationState::CERT_VALID_SIG_INVALID:
                        return DocumentVerificationState::CONTENT_VALID_CERT_VALID_SIG_INVALID;
                    case SignatureVerificationState::CERT_INVALID_SIG_INVALID:
                        return DocumentVerificationState::CONTENT_VALID_CERT_INVALID_SIG_INVALID;
                }
            case ValidationState::INVALID:
                switch (signatureVerificationState) {
                    case SignatureVerificationState::CERT_VALID_SIG_VALID:
                        return DocumentVerificationState::CONTENT_INVALID_CERT_VALID_SIG_VALID;
                    case SignatureVerificationState::CERT_INVALID_SIG_VALID:
                        return DocumentVerificationState::CONTENT_INVALID_CERT_INVALID_SIG_VALID;
                    case SignatureVerificationState::CERT_VALID_SIG_INVALID:
                        return DocumentVerificationState::CONTENT_INVALID_CERT_VALID_SIG_INVALID;
                    case SignatureVerificationState::CERT_INVALID_SIG_INVALID:
                        return DocumentVerificationState::CONTENT_INVALID_CERT_INVALID_SIG_INVALID;
                }
        }
    }

    void PrintedDocumentLinkingSystem::printDocumentVerificationState(DocumentVerificationState state) {
        switch (state) {
            case DocumentVerificationState::CONTENT_VALID_CERT_VALID_SIG_VALID:
                std::cout << "CONTENT_VALID_CERT_VALID_SIG_VALID" << std::endl;
                break;
            case DocumentVerificationState::CONTENT_VALID_CERT_VALID_SIG_INVALID:
                std::cout << "CONTENT_VALID_CERT_VALID_SIG_INVALID" << std::endl;
                break;
            case DocumentVerificationState::CONTENT_VALID_CERT_INVALID_SIG_VALID:
                std::cout << "CONTENT_VALID_CERT_INVALID_SIG_VALID" << std::endl;
                break;
            case DocumentVerificationState::CONTENT_VALID_CERT_INVALID_SIG_INVALID:
                std::cout << "CONTENT_VALID_CERT_INVALID_SIG_INVALID" << std::endl;
                break;
            case DocumentVerificationState::CONTENT_INVALID_CERT_VALID_SIG_VALID:
                std::cout << "CONTENT_INVALID_CERT_VALID_SIG_VALID" << std::endl;
                break;
            case DocumentVerificationState::CONTENT_INVALID_CERT_VALID_SIG_INVALID:
                std::cout << "CONTENT_INVALID_CERT_VALID_SIG_INVALID" << std::endl;
                break;
            case DocumentVerificationState::CONTENT_INVALID_CERT_INVALID_SIG_VALID:
                std::cout << "CONTENT_INVALID_CERT_INVALID_SIG_VALID" << std::endl;
                break;
            case DocumentVerificationState::CONTENT_INVALID_CERT_INVALID_SIG_INVALID:
                std::cout << "CONTENT_INVALID_CERT_INVALID_SIG_INVALID" << std::endl;
                break;
        }
    }

    std::string PrintedDocumentLinkingSystem::readStringFromTerminal(const std::string& prompt) {
        std::string res {""};
        std::cout << prompt << " : ";
        std::cin >> res;
        return res;
    }
}
