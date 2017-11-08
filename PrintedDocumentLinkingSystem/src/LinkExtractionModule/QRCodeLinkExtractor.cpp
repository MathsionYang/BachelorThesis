#include "QRCodeLinkExtractor.h"

#include <zxing/LuminanceSource.h>
#include <zxing/MultiFormatReader.h>
#include <zxing/qrcode/QRCodeReader.h>
#include <zxing/common/GlobalHistogramBinarizer.h>

#include <opencv2/opencv.hpp>

#include "../Util/OpenCVZXingBridgeSource.h"
#include "LinkExtractionModule.h"

namespace PDLS {

    Link* QRCodeLinkExtractor::extractLink(Document* doc, LinkDescription* desc) throw(PDLSException)  {
        if(!doc || !desc)
            throw NullPointerException("LDataLinkExtractionModule::extractLink");

        if(doc->getType() != FileType::PDF && doc->getType() != FileType::IMG)
            throw StrategyMismatchException("QRCodeLinkExtractor::extractLink");

        Document* imgDoc{nullptr};
        std::string linkText{""};

        if(doc->getType() == FileType::PDF)
            //convert pdf to img
            imgDoc= _pdf2imgConverter->convertPDF2Image(doc, 300);

        try {
            //create a QRCode Reader
            zxing::qrcode::QRCodeReader reader;

            //load image of workload doc from file
            cv::Mat img = cv::imread(imgDoc->getPath().string(), CV_LOAD_IMAGE_GRAYSCALE);

            //check if image was loaded successfully
            if (!img.data)
                throw FileNotFoundException(imgDoc->getPath());

            //create ZXing from OpenCV image via OpenCVZXingBridgeSource
            zxing::Ref<OpenCVZXingBridgeSource> source(new OpenCVZXingBridgeSource(img));

            //convert to accepted format for ZXing QR Code Reader
            zxing::Ref<zxing::Binarizer> binarizer(new zxing::GlobalHistogramBinarizer(source));
            zxing::Ref<zxing::BinaryBitmap> bitmap(new zxing::BinaryBitmap(binarizer));

            //search and decode QR code in image
            zxing::Ref<zxing::Result> result(reader.decode(bitmap, zxing::DecodeHints(zxing::DecodeHints::TRYHARDER_HINT)));

            //if successful text of QR is link text
            linkText = result->getText()->getText();
        } catch (zxing::Exception& e) {
            throw QRCodeLinkExtractionException(imgDoc->getPath());
        }

        //delete the converted file if user doesnt want to save it
        if(doc->getType() == FileType::PDF)
            if(!LinkExtractionModule::getInstance()->isSaveConvertedFile())
                imgDoc->removeFromDisk();

        return new Link(linkText, desc);
    }

}
