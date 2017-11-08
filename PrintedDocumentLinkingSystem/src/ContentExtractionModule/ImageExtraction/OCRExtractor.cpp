#include "OCRExtractor.h"

#include <opencv2/opencv.hpp>

#include <leptonica/allheaders.h>



namespace PDLS {

    void OCRExtractor::initTesseract() {
        _tesseractAPI = new tesseract::TessBaseAPI();
        //init without specifying tessdata path -> using default path
        if(_tesseractAPI->Init(nullptr, _ocrLanguage.c_str(), _ocrEngineMode) == -1) {
            throw TesseractInitialisationException(_ocrLanguage, tesseract::OEM_DEFAULT, tesseract::PSM_AUTO);
        }
        _tesseractAPI->SetPageSegMode(tesseract::PSM_AUTO);
    }

    Content* OCRExtractor::extractContent(Document* imgdoc) throw (PDLSException) {

        //load image of workload doc from file
        cv::Mat img = cv::imread(imgdoc->getPath().string(), CV_LOAD_IMAGE_GRAYSCALE);

        //check if image was loaded successfully
        if (img.data) {
            //provide cv::Mat _data to tesseract -> use raw uchar _data from cv::Mat
            _tesseractAPI->SetImage((unsigned char*) img.data, img.cols, img.rows, 1, img.cols);
            _tesseractAPI->Recognize(0);
            std::string ocrResult(_tesseractAPI->GetUTF8Text());
            return new Content(imgdoc, std::move(ocrResult));
        } else
            throw FileNotFoundException(imgdoc->getPath());

    }

}
