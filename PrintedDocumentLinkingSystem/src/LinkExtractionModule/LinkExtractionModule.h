#ifndef PRINTEDDOCUMENTVERIFICATIONSYSTEM_LDataLINKEXTRACTIONMODULE_H
#define PRINTEDDOCUMENTVERIFICATIONSYSTEM_LDataLINKEXTRACTIONMODULE_H


#include "../Datatypes/LinkingData.h"
#include "../Datatypes/Link.h"
#include "../Datatypes/LinkDescription.h"

#include "ILinkExtractor.h"
#include "TextLinkExtractor.h"
#include "QRCodeLinkExtractor.h"

namespace PDLS {

    class LinkExtractionModule {
        ILinkExtractor* _textLinkExtractor;
        ILinkExtractor* _qrCodeLinkExtractor;

        bool _saveConvertedFile;
        bool _extractQRCodeLink;

        LinkExtractionModule() : _textLinkExtractor(new TextLinkExtractor()),
                                 _qrCodeLinkExtractor(new QRCodeLinkExtractor()),
                                 _saveConvertedFile(false),
                                 _extractQRCodeLink(true) { }

    public:

        Link* extractLink(Document* doc, LinkDescription* desc) throw(PDLSException);

        static LinkExtractionModule* getInstance() {
            static LinkExtractionModule singleton;
            return &singleton;
        }

        inline ILinkExtractor* getTextDocumentExtractor() const {
            return _textLinkExtractor;
        }

        inline void setTextDocumentExtractor(ILinkExtractor* textDocumentExtractor) {
            _textLinkExtractor = textDocumentExtractor;
        }

        inline ILinkExtractor* getImageDocumentExtractor() const {
            return _qrCodeLinkExtractor;
        }

        inline void setImageDocumentExtractor(ILinkExtractor* imageDocumentExtractor) {
            _qrCodeLinkExtractor = imageDocumentExtractor;
        }

        inline bool isSaveConvertedFile() const {
            return _saveConvertedFile;
        }

        inline void setSaveConvertedFile(bool saveConvertedFile) {
            _saveConvertedFile = saveConvertedFile;
        }

        inline bool isExtractQRCodeLink() const {
            return _extractQRCodeLink;
        }

        inline void setExtractQRCodeLink(bool extractQRCodeLink) {
            _extractQRCodeLink = extractQRCodeLink;
        }

        LinkExtractionModule(const LinkExtractionModule&) = delete;
        void operator=(const LinkExtractionModule&) = delete;
    };

}

#endif //PRINTEDDOCUMENTVERIFICATIONSYSTEM_LDataLINKEXTRACTIONMODULE_H
