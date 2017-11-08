#ifndef PRINTEDDOCUMENTVERIFICATIONSYSTEM_PDVSEXCEPTION_H
#define PRINTEDDOCUMENTVERIFICATIONSYSTEM_PDVSEXCEPTION_H

#include <sstream>
#include <string>

#include <boost/filesystem.hpp>
#include <tesseract/baseapi.h>

namespace PDLS {
    namespace bfs = boost::filesystem;

    class PDLSException : public std::exception {
    protected:
        std::stringstream _msgBuffer;
        std::string _msg;

    public:
        PDLSException() { _msgBuffer << "PrintedDocumentLinkingSystem Exception: " << std::endl; }

        virtual const char* what() const noexcept override {
            return _msg.c_str();
        }
    };

    class NullPointerException : public PDLSException {
    public:
        NullPointerException(const std::string& functionName) {
            _msgBuffer << "Null Pointer Exception: " << std::endl;
            _msgBuffer << "Function '" << functionName << "' was handed a null pointer !" << std::endl;
            _msg = _msgBuffer.str();
        }
    };

    class FileNotFoundException : public PDLSException {
    public:
        FileNotFoundException(const bfs::path& p) {
            _msgBuffer << "File Not Found Exception: " << std::endl;
            _msgBuffer << "Cannot load file: '" << p.string() << "'" << std::endl;
            _msg = _msgBuffer.str();
        }
    };

    class UnsupportedFileException : public PDLSException {
    public:
        UnsupportedFileException(const bfs::path& p) {
            _msgBuffer << "Unsupported File Exception: " << std::endl;
            _msgBuffer << "File '" << p.string() << "' is not supported!";
            _msg = _msgBuffer.str();
        }
    };

    class SavingFileException : public PDLSException {
    public:
        SavingFileException(const bfs::path& p) {
            _msgBuffer << "Saving File Exception!" << std::endl;
            _msgBuffer << "Cannot write file: '"<< p.string() << "'!" << std::endl;
        }
    };

    class NoStrategyException : public PDLSException {
    public:
        NoStrategyException(const char* module) {
            _msgBuffer << "No Strategy Exception!" << std::endl;
            _msgBuffer << "No strategy for module " << module << "instantiated!" << std::endl;
        }
    };

    class NoProviderException : public PDLSException {
    public:
        NoProviderException(const char* module) {
            _msgBuffer << "No Provider Exception!" << std::endl;
            _msgBuffer << "No Provider is set for module " << module << "!" << std::endl;
        }
    };

    class TesseractInitialisationException : public PDLSException {
    public:
        TesseractInitialisationException(std::string& lang, tesseract::OcrEngineMode oem, tesseract::PageSegMode psm) {
            _msgBuffer << "Tesseract Initialisation Exception: " << std::endl;
            _msgBuffer << "Cannot initialize Tesseract API!" << std::endl;
            _msgBuffer << "Language: " << lang << std::endl
            << "ImageExtraction Enging Mode: " << oem << std::endl
            << "Page Segmentation Mode: " << psm;
            _msg = _msgBuffer.str();
        }
    };

    class GhostScriptInitializationException : public PDLSException {
    public:
        GhostScriptInitializationException() {
            _msgBuffer << "GhostScript Initialization Exception: " << std::endl;
            _msgBuffer << "Error while initialization of GhostScript API!";
            _msg = _msgBuffer.str();
        }
    };

    class ContentHashGenerationException : public PDLSException {
    public:
        ContentHashGenerationException() { //TODO hashtype ausgabe
            _msgBuffer << "Content Hash Generation Exception: " << std::endl;
            _msgBuffer << "LibOpenSSL error while generating Content-Hash of Type '"<< "hashType" <<"'!"; //TODO
            _msg = _msgBuffer.str();
        }
    };

    class InvalidContentHashException : public PDLSException {
    public:
        InvalidContentHashException(const std::string& cH, const std::string& pre, const std::string& post) {
            _msgBuffer << "Invalid Content Hash Exception: " << std::endl;
            _msgBuffer << "The provided Content-Hash '"<< pre << cH.c_str() << post << "' does not fit in any type!";
            _msg = _msgBuffer.str();
        }
    };

    class OpenSSLRSAPublicKeyObjectExtractionException : public PDLSException {
    public:
        OpenSSLRSAPublicKeyObjectExtractionException(const bfs::path& certificateFile) {
            _msgBuffer << "OpenSSL RSA Key Object Extraction Exception: " << std::endl;
            _msgBuffer << "LibOpenSSL error while extracting RSA Key Object from certificate'"<< certificateFile.string() <<"'!";
            _msg = _msgBuffer.str();
        }
    };

    class OpenSSLRSAPrivateKeyObjectCreationException : public PDLSException {
    public:
        OpenSSLRSAPrivateKeyObjectCreationException(const bfs::path& keyPem) {
            _msgBuffer << "OpenSSL RSA Private Key Object Creation Exception: " << std::endl;
            _msgBuffer << "LibOpenSSL error while creating RSA Private Key Object from key file '"<< keyPem.string() <<"'!";
            _msg = _msgBuffer.str();
        }
    };


    class OpenSSLEVPKeyObjectExtractionException : public PDLSException {
    public:
        OpenSSLEVPKeyObjectExtractionException(const bfs::path& certificateFile) {
            _msgBuffer << "OpenSSL EVP Key Object Extraction Exception: " << std::endl;
            _msgBuffer << "LibOpenSSL error while extracting EVP Key Object from certificate '"<< certificateFile.string() <<"'!";
            _msg = _msgBuffer.str();
        }
    };

    class OpenSSLX509ObjectCreationException : public PDLSException {
    public:
        OpenSSLX509ObjectCreationException(const bfs::path& certificateFile) {
            _msgBuffer << "OpenSSL X509 Object Creation Exception: " << std::endl;
            _msgBuffer << "LibOpenSSL error while creating X509 Object from certificate '"<< certificateFile.string() <<"'!";
            _msg = _msgBuffer.str();
        }
    };

    class RSASignatureGenerationException : public PDLSException {
    public:
        RSASignatureGenerationException(/*const ContentHash* doc, const bfs::path& pkFile*/) { //TODO
            _msgBuffer << "RSA Signature Generation Exception: " << std::endl;
            _msgBuffer << "LibOpenSSL error while generating RSA Signature from Content-Hash! '" /*<< doc->getPat().string() << "'"*/ << std::endl;
            _msgBuffer << " & RSA Private Key '" /* << pkFile.string() << "'"*/;
            _msg = _msgBuffer.str();
        }
    };

    class MissingPrivateKeyException : public PDLSException {
    public:
        MissingPrivateKeyException() {
            _msgBuffer << "Missing PrivateKey Exception: " << std::endl;
            _msgBuffer << "PrivateKey to generate Signature is missing!" << std::endl;
            _msg = _msgBuffer.str();
        }
    };

    class KeyTypeMismatchException : public PDLSException {
    public:
        KeyTypeMismatchException(const std::string& keyName, const std::string& actionName) {
            _msgBuffer << "Key Type Mismatch Exception: " << std::endl;
            _msgBuffer << "Type of Key '" << keyName << "' does not match required action '" << actionName << "' !" << std::endl;
            _msg = _msgBuffer.str();
        }
    };

    class ContentValidationException : public PDLSException {
    public:
        ContentValidationException(const std::string& msg) {
            _msgBuffer << "Content Validation Exception: " << std::endl;
            _msgBuffer << msg;
            _msg = _msgBuffer.str();
        }
    };

    class MissingContentHashException : public PDLSException {
    public:
        MissingContentHashException(const bfs::path& p) {
            _msgBuffer << "Missing Content Hash Exception! " << std::endl;
            _msgBuffer << "The provided document '" << p.string() << "' does not contain a valid Content-Hash!" << std::endl;
            _msg = _msgBuffer.str();
        }
    };

    class TooManyContentHashesException : public PDLSException {
    public:
        TooManyContentHashesException(const bfs::path& p) {
            _msgBuffer << "Too Many Content Hashes Exception! " << std::endl;
            _msgBuffer << "The provided document '" << p.string() << "' contains more than one Content-Hash!" << std::endl;
            _msg = _msgBuffer.str();
        }
    };

    class LDataMissingSignatureException : public PDLSException {
    public:
        LDataMissingSignatureException() {
            _msgBuffer << "Document Linking Data Exception! " << std::endl;
            _msgBuffer << "Cannot generate Document Registration Data due to missing Signature!" << std::endl;
            _msg = _msgBuffer.str();
        }
    };

    class LDataMissingX509CertificateException : public PDLSException {
    public:
        LDataMissingX509CertificateException() {
            _msgBuffer << "Document Linking Data Exception! " << std::endl;
            _msgBuffer << "Cannot generate Document Registration Data due to missing Public Key!" << std::endl;
            _msg = _msgBuffer.str();
        }
    };

    class LDataMissingContentHashException : public PDLSException {
    public:
        LDataMissingContentHashException() {
            _msgBuffer << "Document Linking Data Exception! " << std::endl;
            _msgBuffer << "Cannot generate Document Registration Data due to missing Content-Hash!" << std::endl;
            _msg = _msgBuffer.str();
        }
    };

    class SVMMissingSignatureException : public PDLSException {
    public:
        SVMMissingSignatureException() {
            _msgBuffer << "Signature Verification Exception! " << std::endl;
            _msgBuffer << "Cannot verify Document due to missing Signature!" << std::endl;
            _msg = _msgBuffer.str();
        }
    };

    class SVMMissingCertificateException : public PDLSException {
    public:
        SVMMissingCertificateException() {
            _msgBuffer << "Signature Verification Exception! " << std::endl;
            _msgBuffer << "Cannot verify Document due to missing Certificate!" << std::endl;
            _msg = _msgBuffer.str();
        }
    };

    class SVMMissingContentHashException : public PDLSException {
    public:
        SVMMissingContentHashException() {
            _msgBuffer << "Signature Verification Exception! " << std::endl;
            _msgBuffer << "Cannot verify Document due to missing Content Hash!" << std::endl;
            _msg = _msgBuffer.str();
        }
    };

    class LinkInjectionException : public PDLSException {
    public:
        LinkInjectionException(const std::string& detail) {
            _msgBuffer << "Link Injection Exception! " << std::endl;
            _msgBuffer << "Cannot inject Link into Document!" << std::endl;
            _msgBuffer << "Detail: " << detail << std::endl;
            _msg = _msgBuffer.str();
        }
    };

    class MissingLinkException : public PDLSException {
    public:
        MissingLinkException(const bfs::path& p, const std::string& content) {
            _msgBuffer << "Missing LData Link Exception! " << std::endl;
            _msgBuffer << "The provided document '" << p.string() << "' does not contain a valid Link!" << std::endl;
            _msgBuffer << std::endl << "Content: " << std::endl << content;
            _msg = _msgBuffer.str();
        }
    };

    class TooManyLinksException : public PDLSException {
    public:
        TooManyLinksException(const bfs::path& p, const std::string& content) {
            _msgBuffer << "Too Many Content Hasher Exception! " << std::endl;
            _msgBuffer << "The provided document '" << p.string() << "' contains more than one Link!" << std::endl;
            _msgBuffer << std::endl << "Content: " << std::endl << content;
            _msg = _msgBuffer.str();
        }
    };

    class StrategyMismatchException : public PDLSException {
    public:
        StrategyMismatchException(const std::string& fName) {
            _msgBuffer << "Strategy Mismatch Exception! " << std::endl;
            _msgBuffer << "The selected strategy to perfom action '" << fName << "' does not match the provided input!"  << std::endl;
            _msg = _msgBuffer.str();
        }
    };

    class LinkMismatchException : public PDLSException {
    public:
        LinkMismatchException(const std::string& lName, const std::string& pName) {
            _msgBuffer << "Link Mismatch Exception! " << std::endl;
            _msgBuffer << "The Link '" << lName << "' cannot be downloaded at Provider '" << pName << "'! " << std::endl;
            _msg = _msgBuffer.str();
        }
    };

    class LinkDescriptionMismatchException : public PDLSException {
    public:
        LinkDescriptionMismatchException(const std::string& link, const std::string& provider, const std::string& matcher) {
            _msgBuffer << "Link Description Missmatch Exception! " << std::endl;
            _msgBuffer << "The Link '" << link << "' cannot be created because it does not fit the LinkDescription:" << std::endl;
            _msgBuffer << "Provider: '" << provider << "'" << std::endl;
            _msgBuffer << "Regex Matcher: '" << matcher << "'" << std::endl;
            _msg = _msgBuffer.str();
        }
    };

    class IPFSConnectionException : public PDLSException {
    public:
        IPFSConnectionException(const std::string& errorMsg) {
            _msgBuffer << "IPFS Connection Exception! " << std::endl;
            _msgBuffer << "Cannot connect to IPFS! Is ipfs daemon running and swarm peers connected?"  << std::endl;
            _msgBuffer << "Error: " << errorMsg << std::endl;
            _msg = _msgBuffer.str();
        }
    };

    class LinkingDataJSONFormatException : public PDLSException {
    public:
        LinkingDataJSONFormatException(const std::string& missingKey) {
            _msgBuffer << "Linking Data JSON Format Exception! " << std::endl;
            _msgBuffer << "Cannot convert JSON-String to LinkingData object!"  << std::endl;
            _msgBuffer << "Missing Key: " << missingKey << std::endl;
            _msg = _msgBuffer.str();
        }
    };

    class QRCodeLinkExtractionException : public MissingLinkException {
    public:
        QRCodeLinkExtractionException(const bfs::path& p)
                : MissingLinkException(p, "QR-Code") {
            _msgBuffer << "QR Code Link Extraction Exception! " << std::endl;
            _msgBuffer << "Cannot extract QR Code Link from document!!"  << std::endl;
            _msg = _msgBuffer.str();
        }
    };



}

#endif //PRINTEDDOCUMENTVERIFICATIONSYSTEM_PDVSEXCEPTION_H
