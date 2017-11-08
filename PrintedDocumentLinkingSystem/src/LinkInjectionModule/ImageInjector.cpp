#include "ImageInjector.h"

namespace PDLS {

    void ImageInjector::injectLink(Document* imgDoc, Link* l, const bfs::path& out) throw(PDLSException) {
        if(imgDoc == nullptr || l == nullptr)
            throw NullPointerException("ImageInjector::injectLink");
        if(imgDoc->getType() != FileType::IMG)
            throw StrategyMismatchException("ImageInjector::injectLink");

        //load image of workload doc from file
        cv::Mat img = cv::imread(imgDoc->getPath().string(), CV_LOAD_IMAGE_GRAYSCALE);

        cv::Mat outPutImage;
        if(!_injectQR)
            outPutImage = injectLinkText(l, img);
        else
            outPutImage = injectQRLink(l, img);

        saveOutoutImage(out, outPutImage);
    }

    void ImageInjector::saveOutoutImage(const bfs::path& out, const cv::Mat& outPutImage) const {
        //set compression parameters for output image -> file type png
        //See http://docs.opencv.org/3.0-beta/modules/imgcodecs/doc/reading_and_writing_images.html?highlight=imwrite#cv2.imwrite
        std::vector<int> compression_params;
        compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
        compression_params.push_back(9);

        //save image to disk
        try {
            imwrite(out.string(), outPutImage, compression_params);
        } catch (std::runtime_error& re) {
            throw SavingFileException(out);
        }
    }

    cv::Mat& ImageInjector::injectLinkText(Link* l, cv::Mat& img) throw(PDLSException) {//calc the size of the text
        int baseline = 0;
        cv::Size textSize = getTextSize(l->getInjectionString(), _font, _fontScale, _fontThickness, &baseline);

        //start position injected link text in image
        cv::Point textPos;
        if(_xPos < 0 || _yPos < 0) // default values are close to the very bottom of the image
            textPos = cv::Point(img.cols - textSize.width - 10, img.rows - textSize.height - 10);
        else
            textPos = cv::Point(_xPos, _yPos);

        if(_drawBoundingBox)
            //draw bounding box that contains link text
            rectangle(img, textPos + cv::Point(0, baseline + 10), textPos + cv::Point(textSize.width, -textSize.height - 10),
                      _textColor);

        //inject text into img
        //See http://docs.opencv.org/3.0-beta/modules/imgproc/doc/drawing_functions.html?highlight=puttext#puttext
        putText(img, l->getInjectionString(), textPos, _font, _fontScale, cv::Scalar(0, 255, 0), _fontThickness, cv::FILLED);

        return img;
    }

    cv::Mat& ImageInjector::injectQRLink(Link* l, cv::Mat& img) throw(PDLSException) {
        // generate qr code from link injection text
        qrcodegen::QrCode qr0 = qrcodegen::QrCode::encodeText(l->getInjectionString().c_str(), _qrErrorCorrectionLevel);

        // transform qr code modules into bits
        int k = 0;
        int white = 255;
        int black = 0;
        unsigned char qrModuleBits[qr0.size][qr0.size];
        for (int y = 0; y < qr0.size; y++) {
            for (int x = 0; x < qr0.size; x++) {
                // white is 0(false), black is 1 (true)
                qrModuleBits[y][x] =  (qr0.getModule(x, y) ? black : white); //caution! qrModuleBits[y][x] is NOT an error but mandatory
            }
        }

        //convert module bits into opencv image
        cv::Mat qrCodeRawMatrix(qr0.size, qr0.size, CV_8UC1, qrModuleBits);

        //scale raw matrix by _qrModulePixelSize
        cv::Mat qrCode;
        cv::resize(qrCodeRawMatrix, qrCode, cv::Size(), _qrModulePixelSize, _qrModulePixelSize, cv::INTER_NEAREST);

        //create the border around the qr
        copyMakeBorder(qrCode, qrCode, _qrBorderThinkness, _qrBorderThinkness, _qrBorderThinkness, _qrBorderThinkness, cv::BORDER_CONSTANT, cv::Scalar(255, 255, 255));

        //calc injection position in image
        int padding = 25;
        cv::Point injectionRoIOrigin;
        injectionRoIOrigin = cv::Point(img.cols - qrCode.cols - padding, img.rows - qrCode.rows - padding);

        //create injection RoI where qrCode gets injected
        cv::Rect injectionRoI(injectionRoIOrigin, cv::Size(qrCode.cols, qrCode.rows));

        //inject qrCode
        qrCode.copyTo(img(injectionRoI));

        return img;
    }


}