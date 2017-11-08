#ifndef PRINTEDDOCUMENTVERIFICATIONSYSTEM_LDataLINKINJECTIONMODULE_H
#define PRINTEDDOCUMENTVERIFICATIONSYSTEM_LDataLINKINJECTIONMODULE_H

#include "../Datatypes/Document.h"
#include "../Datatypes/Link.h"
#include "ILinkInjector.h"
#include "XMLInjector.h"
#include "ImageInjector.h"
#include "TextInjector.h"
#include "PDFInjector.h"

namespace PDLS {

    class LinkInjectionModule {

        bool _saveConvertedDocument;

        ILinkInjector* _textInjectionstrategy;
        ILinkInjector* _xmlInjectionstrategy;
        ILinkInjector* _imageInjectionstrategy;
        ILinkInjector* _pdfInjectionstrategy;

        LinkInjectionModule() : _textInjectionstrategy(nullptr),
                                _xmlInjectionstrategy(nullptr),
                                _imageInjectionstrategy(nullptr),
                                _pdfInjectionstrategy(nullptr),
                                _saveConvertedDocument(false) {createDefaultStrategies();}

    public:

        void injectLink(Document* doc, Link* link, const bfs::path& out) throw(PDLSException);

        static LinkInjectionModule* getInstance() {
            static LinkInjectionModule singleton;
            return &singleton;
        }

        void createDefaultStrategies() {
            _textInjectionstrategy = new TextInjector();
            _xmlInjectionstrategy = new XMLInjector("fo:root/fo:page-sequence/fo:static-content",
                                                    std::list<std::string>{"fo:block", "fo:inline"});
            _imageInjectionstrategy = new ImageInjector();
            _pdfInjectionstrategy = new PDFInjector();
        }

        inline ILinkInjector* getStrategy() const {
            return _textInjectionstrategy;
        }

        inline void setStrategy(ILinkInjector* strategy) {
            _textInjectionstrategy = strategy;
        }

        bool isSaveConvertedDocument() const {
            return _saveConvertedDocument;
        }

        void setSaveConvertedDocument(bool saveConvertedDocument) {
            _saveConvertedDocument = saveConvertedDocument;
        }

        LinkInjectionModule(const LinkInjectionModule&) = delete;
        void operator=(const LinkInjectionModule&) = delete;
    };

}

#endif //PRINTEDDOCUMENTVERIFICATIONSYSTEM_LDataLINKINJECTIONMODULE_H
