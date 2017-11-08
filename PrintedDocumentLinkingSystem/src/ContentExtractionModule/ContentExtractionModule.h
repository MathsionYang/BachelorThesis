#ifndef CONTENTEXTRACTIONMODULE_CONTENTEXTRACTIONMODULE_H
#define CONTENTEXTRACTIONMODULE_CONTENTEXTRACTIONMODULE_H

#include <iostream>
#include "../Datatypes/PDLSException.h"
#include "../Datatypes/EnumTypes.h"

#include "IExtractionStrategy.h"

namespace PDLS {

    class ContentExtractionModule {
        //flag that indicates wether the PDF should be treated as a pdf that contains text or an image pdf that contains no text
        bool _inputTreatedAsTextPDF;
        bool _saveConvertedDocument;

        IExtractionStrategy* _imageExtractionStrategy;
        IExtractionStrategy* _textPDFExtractionStrategy;
        IExtractionStrategy* _imagePDFExtractionStrategy;
        IExtractionStrategy* _xmlExtractionStrategy;

        ContentExtractionModule() : _inputTreatedAsTextPDF(false),
                                    _saveConvertedDocument(false),
                                    _imageExtractionStrategy(nullptr),
                                    _textPDFExtractionStrategy(nullptr),
                                    _imagePDFExtractionStrategy(nullptr),
                                    _xmlExtractionStrategy(nullptr)
        { createDefaultStrategies(); }

        ~ContentExtractionModule() {
            delete _imageExtractionStrategy;
            delete _imagePDFExtractionStrategy;
            delete _textPDFExtractionStrategy;
            delete _xmlExtractionStrategy;
        }

    public:

        void createDefaultStrategies();

        static ContentExtractionModule* getInstance() {
            static  ContentExtractionModule singleton;
            return &singleton;
        }

        Content* extractContent(Document* doc) throw(PDLSException);

        inline IExtractionStrategy* getImageExtractionStrategy() const {
            return _imageExtractionStrategy;
        }

        inline void setImageExtractionStrategy(IExtractionStrategy* imageExtractionStrategy) {
            if(_imageExtractionStrategy != nullptr) delete _imageExtractionStrategy;
            _imageExtractionStrategy = imageExtractionStrategy;
        }

        inline IExtractionStrategy* getTextPDFExtractionStrategy() const {
            return _textPDFExtractionStrategy;
        }

        inline void setTextPDFExtractionStrategy(IExtractionStrategy* textPDFExtractionStrategy) {
            if(_textPDFExtractionStrategy != nullptr) delete _textPDFExtractionStrategy;
            _textPDFExtractionStrategy = textPDFExtractionStrategy;
        }

        inline IExtractionStrategy* getImagePDFExtractionStrategy() const {
            return _imagePDFExtractionStrategy;
        }

        inline void setImagePDFExtractionStrategy(IExtractionStrategy* imagePDFExtractionStrategy) {
            if(_imagePDFExtractionStrategy != nullptr) delete _imagePDFExtractionStrategy;
            _imagePDFExtractionStrategy = imagePDFExtractionStrategy;
        }

        inline IExtractionStrategy* getXmlExtractionStrategy() const {
            return _xmlExtractionStrategy;
        }

        inline void setXmlExtractionStrategy(IExtractionStrategy* xmlExtractionStrategy) {
            if(_xmlExtractionStrategy != nullptr) delete _xmlExtractionStrategy;
            _xmlExtractionStrategy = xmlExtractionStrategy;
        }

        inline bool isInputTreatedAsTextPDF() const {
            return _inputTreatedAsTextPDF;
        }

        inline void treatInputPDFAsTextPDF(bool inputTreatedAsTextPDF) {
            _inputTreatedAsTextPDF = inputTreatedAsTextPDF;
        }


        bool saveConvertedDocument() const {
            return _saveConvertedDocument;
        }

        void saveConvertedDocument(bool saveConvertedDocument) {
            _saveConvertedDocument = saveConvertedDocument;
        }

        ContentExtractionModule(const ContentExtractionModule&) = delete;
        void operator=(const ContentExtractionModule&) = delete;
    };

}

#endif //CONTENTEXTRACTIONMODULE_CONTENTEXTRACTIONMODULE_H
