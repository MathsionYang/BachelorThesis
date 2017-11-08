#ifndef PRINTEDDOCUMENTVERIFICATIONSYSTEM_DOCUMENTREGISTRATIONMETADATA_H
#define PRINTEDDOCUMENTVERIFICATIONSYSTEM_DOCUMENTREGISTRATIONMETADATA_H

#include <nlohmann/json.hpp>

#include "PDLSException.h"

namespace PDLS {


    //forward decl
    class Document;
    class Signature;
    class ContentHash;
    class X509Certificate;

    class LinkingData {
        std::string _documentName;

        Signature* _signature;
        std::string _signatureEncoding;
        std::string _signatureData;

        ContentHash* _contentHash;
        std::string _contentHashType;
        std::string _contentHashPrefix;
        std::string _contentHashPostfix;
        std::string _contentHashData;

        X509Certificate* _cert;
        std::string _certType;
        std::string _certData;

        std::string _jsonString;

    public:

        LinkingData(const std::string& docN,
                     const std::string& sigEnc,
                     const std::string& sigData,
                     const std::string& chType,
                     const std::string& chPrefix,
                     const std::string& chPostfix,
                     const std::string& chData,
                     const std::string& certData,
                     const std::string& certType = "X509") : _documentName(docN),
                                                            _signature(nullptr),
                                                            _signatureEncoding(sigEnc),
                                                            _signatureData(sigData),
                                                            _contentHash(nullptr),
                                                            _contentHashType(chType),
                                                            _contentHashPrefix(chPrefix),
                                                            _contentHashPostfix(chPostfix),
                                                            _contentHashData(chData),
                                                            _certData(certData),
                                                            _certType(certType),
                                                            _cert(nullptr) { }

        LinkingData(const std::string& JSONString) throw(PDLSException);

        LinkingData(Document* doc, X509Certificate* cert);

        const std::string& convertToJSON();

        inline const std::string& getSignatureEncoding() const {
            return _signatureEncoding;
        }

        inline void setSignatureEncoding(const std::string& signatureEncoding) {
            _signatureEncoding = signatureEncoding;
        }

        inline const std::string& getSignatureData() const {
            return _signatureData;
        }

        inline void setSignatureData(const std::string& signatureData) {
            _signatureData = signatureData;
        }

        inline const std::string& getContentHashType() const {
            return _contentHashType;
        }

        inline void setContentHashType(const std::string& contentHashType) {
            _contentHashType = contentHashType;
        }

        inline const std::string& getContentHashData() const {
            return _contentHashData;
        }

        inline void setContentHashData(const std::string& contentHashData) {
            _contentHashData = contentHashData;
        }


        inline const std::string& getCertType() const {
            return _certType;
        }

        inline void setCertType(const std::string& certType) {
            _certType = certType;
        }

        inline const std::string& getCertData() const {
            return _certData;
        }

        inline void setCertData(const std::string& certData) {
            _certData = certData;
        }

        inline const std::string& getDocumentName() const {
            return _documentName;
        }

        inline void setDocumentName(const std::string& documentName) {
            _documentName = documentName;
        }

        inline const std::string& getJsonString() {
            if(_jsonString.size() == 0) convertToJSON();
            return _jsonString;
        }

        X509Certificate* getCertificate();

        ContentHash* getContentHash();

        Signature* getSignature();
    };

}

#endif //PRINTEDDOCUMENTVERIFICATIONSYSTEM_DOCUMENTREGISTRATIONMETADATA_H
