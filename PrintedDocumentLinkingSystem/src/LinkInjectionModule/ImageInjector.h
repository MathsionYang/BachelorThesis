#ifndef PRINTEDDOCUMENTLINKINGSYSTEM_IMAGEINJECTOR_H
#define PRINTEDDOCUMENTLINKINGSYSTEM_IMAGEINJECTOR_H

#include "ILinkInjector.h"
#include "../Datatypes/Link.h"
#include "../Util/nayukiQRCodeGen/QrCode.hpp"

#include <opencv2/opencv.hpp>
namespace PDLS {

    class ImageInjector : public ILinkInjector {

        //flag that indicates wether qrcode or linktext is injected
        bool _injectQR;

        //position of injection
        int _xPos;
        int _yPos;

        //qrcode injection settings
        int _qrModulePixelSize;
        int _qrBorderThinkness;
        qrcodegen::QrCode::Ecc _qrErrorCorrectionLevel;

        //link text injection settings
        cv::HersheyFonts _font;
        double _fontScale;
        int _fontThickness;
        bool _drawBoundingBox;
        cv::Scalar _textColor;

        //inject link text to img
        cv::Mat& injectLinkText(Link* l, cv::Mat& img) throw(PDLSException);
        //inject qr link
        cv::Mat& injectQRLink(Link* l, cv::Mat& img) throw(PDLSException);


        void saveOutoutImage(const boost::filesystem::path& out, const cv::Mat& outPutImage) const;

    public:
        ImageInjector() : _font(cv::FONT_HERSHEY_PLAIN),
                          _fontScale(4.0),
                          _fontThickness(2),
                          _xPos(-1),
                          _yPos(-1),
                          _drawBoundingBox(true),
                          _textColor(cv::Scalar(0, 0, 0)),
                          _injectQR(true),
                          _qrModulePixelSize(5),
                          _qrErrorCorrectionLevel(qrcodegen::QrCode::Ecc::HIGH),
                          _qrBorderThinkness(2 * _qrModulePixelSize) {}

        virtual void injectLink(Document* imgDoc, Link* l, const bfs::path& out) throw(PDLSException) override;


        inline cv::HersheyFonts getFont() const {
            return _font;
        }

        inline void setFont(cv::HersheyFonts font) {
            _font = font;
        }

        inline double getFontScale() const {
            return _fontScale;
        }

        inline void setFontScale(double fontScale) {
            _fontScale = fontScale;
        }

        inline int getFontThickness() const {
            return _fontThickness;
        }

        inline void setFontThickness(int fontThickness) {
            _fontThickness = fontThickness;
        }

        inline int getXPos() const {
            return _xPos;
        }

        inline void setXPos(int xPos) {
            _xPos = xPos;
        }

        inline int getYPos() const {
            return _yPos;
        }

        inline void setYPos(int yPos) {
            _yPos = yPos;
        }

        inline bool isDrawBoundingBox() const {
            return _drawBoundingBox;
        }

        inline void setDrawBoundingBox(bool drawBoundingBox) {
            _drawBoundingBox = drawBoundingBox;
        }

        inline bool isInjectQR() const {
            return _injectQR;
        }

        inline void setInjectQR(bool injectQR) {
            _injectQR = injectQR;
        }


        inline int getQrModulePixelSize() const {
            return _qrModulePixelSize;
        }

        inline void setQrModulePixelSize(int qrModulePixelSize) {
            _qrModulePixelSize = qrModulePixelSize;
        }

        inline int getQrBorderThinkness() const {
            return _qrBorderThinkness;
        }

        inline void setQrBorderThinkness(int qrBorderThinkness) {
            _qrBorderThinkness = qrBorderThinkness;
        }

        inline const qrcodegen::QrCode::Ecc& getQrErrorCorrectionLevel() const {
            return _qrErrorCorrectionLevel;
        }

        inline const cv::Scalar& getTextColor() const {
            return _textColor;
        }

        inline void setTextColor(const cv::Scalar& color) {
            _textColor = color;
        }
    };

}

#endif //PRINTEDDOCUMENTLINKINGSYSTEM_IMAGEINJECTOR_H
