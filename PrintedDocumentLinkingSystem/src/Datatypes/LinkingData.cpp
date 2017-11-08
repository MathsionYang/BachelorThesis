#include "LinkingData.h"

#include <boost/algorithm/string.hpp>

#include "Document.h"
#include "ContentHash.h"
#include "X509Certificate.h"
#include "Signature.h"

namespace PDLS {

    const std::string& LinkingData::convertToJSON()  {
        // create a JSON object
        nlohmann::json json;
        json["DocumentName"] = _documentName;

        json["Signature"]["Encoding"] = _signatureEncoding;
        json["Signature"]["Data"] = _signatureData;


        json["ContentHash"]["Type"] = _contentHashType;
        json["ContentHash"]["Prefix"] = _contentHashPrefix;
        json["ContentHash"]["Postfix"] = _contentHashPostfix;
        json["ContentHash"]["Data"] = _contentHashData;

        json["Certificate"]["Type"] = _certType;
        json["Certificate"]["Data"] = _certData;

        std::stringstream ss;
        ss << std::setw(4) << json;

        _jsonString = ss.str();
        return _jsonString;
    }

    LinkingData::LinkingData(Document* doc, X509Certificate* cert)  : _contentHash(nullptr),
                                                                      _signature(nullptr),
                                                                      _cert(nullptr) {
        if(doc->getSignature() == nullptr)
            throw LDataMissingSignatureException();
        else if(doc->getContentHash() == nullptr)
            throw LDataMissingContentHashException();
        else if(cert == nullptr)
            throw LDataMissingX509CertificateException();

        _documentName = doc->getPath().filename().string();
        _signatureEncoding = "Base64";
        _signatureData = doc->getSignature()->getBase64Signature();
        _contentHashType = doc->getContentHash()->getTypeString();
        _contentHashPrefix = doc->getContentHash()->getPrefix();
        _contentHashPostfix = doc->getContentHash()->getPostfix();
        _contentHashData = doc->getContentHash()->getStringHash();
        _certType = "X509";
        _certData = cert->getPem()->getContentAsString();

        convertToJSON();
    }

    LinkingData::LinkingData(const std::string& JSONString) throw(PDLSException) : _contentHash(nullptr),
                                                                                   _signature(nullptr),
                                                                                   _cert(nullptr) {
        try {
            auto json = nlohmann::json::parse(JSONString);

            _documentName = json["DocumentName"];
            if(_documentName.empty())
                throw LinkingDataJSONFormatException("DocumentName");

            _signatureEncoding = json["Signature"]["Encoding"];
            if(_documentName.empty())
                throw LinkingDataJSONFormatException("Signature:Encoding");

            _signatureData = json["Signature"]["Data"];
            if(_documentName.empty())
                throw LinkingDataJSONFormatException("Signature:Data");

            _contentHashType = json["ContentHash"]["Type"];
            if(_documentName.empty())
                throw LinkingDataJSONFormatException("ContentHash:Type");

            _contentHashPrefix = json["ContentHash"]["Prefix"];
            if(_documentName.empty())
                throw LinkingDataJSONFormatException("ContentHash:Prefix");

            _contentHashPostfix = json["ContentHash"]["Postfix"];
            if(_documentName.empty())
                throw LinkingDataJSONFormatException("ContentHash:Postfix");

            _contentHashData = json["ContentHash"]["Data"];
            if(_documentName.empty())
                throw LinkingDataJSONFormatException("ContentHash:Data");

            _certType = json["Certificate"]["Type"];
            if(_documentName.empty())
                throw LinkingDataJSONFormatException("ContentHash:Type");

            _certData = json["Certificate"]["Data"];
            if(_documentName.empty())
                throw LinkingDataJSONFormatException("ContentHash:Data");
        } catch(...) {
            throw LinkingDataJSONFormatException("String to deserialize LinkingData is not in valid JSON format!");
        }
    }

    ContentHash* LinkingData::getContentHash() {
        if(_contentHash ==  nullptr)
            _contentHash = new ContentHash(ContentHash::getTypeFromString(_contentHashType),
                                           _contentHashData,
                                           _contentHashPrefix,
                                           _contentHashPostfix);
        return _contentHash;
    }

    Signature* LinkingData::getSignature() {
        if(_signature ==  nullptr)
            _signature = new Signature(_signatureData);
        return _signature;
    }

    X509Certificate* LinkingData::getCertificate() {
        if(_cert ==  nullptr)
            _cert =  new X509Certificate(_certData);
        return _cert;
    }


}

