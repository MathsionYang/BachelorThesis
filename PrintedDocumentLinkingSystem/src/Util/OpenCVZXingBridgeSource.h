#ifndef PRINTEDDOCUMENTLINKINGSYSTEM_OPENCVZXINGBRIDGEBITMAPSOURCE_H
#define PRINTEDDOCUMENTLINKINGSYSTEM_OPENCVZXINGBRIDGEBITMAPSOURCE_H

#include <zxing/LuminanceSource.h>
#include <opencv2/opencv.hpp>

namespace PDLS {

    //bridge class from OpenCV to ZXing
    class OpenCVZXingBridgeSource final : public zxing::LuminanceSource {
    private:
        cv::Mat _image;

    public:
        OpenCVZXingBridgeSource(cv::Mat& image) : zxing::LuminanceSource(image.cols, image.rows) {
            _image = image.clone();
        }

        inline int getWidth() const { return _image.cols; }
        inline int getHeight() const { return _image.rows; }

        zxing::ArrayRef<char> getRow(int y, zxing::ArrayRef<char> row) const {
            int width_ = getWidth();
            if (!row) row = zxing::ArrayRef<char>(width_);
            const char *p = _image.ptr<char>(y);
            for (int x = 0; x < width_; ++x, ++p) row[x] = *p;
            return row;
        }

        zxing::ArrayRef<char> getMatrix() const {
            int width_ = getWidth();
            int height_ = getHeight();
            zxing::ArrayRef<char> matrix = zxing::ArrayRef<char>(width_ * height_);
            for (int y = 0; y < height_; ++y) {
                const char *p = _image.ptr<char>(y);
                for (int x = 0; x < width_; ++x, ++p) {
                    matrix[y * width_ + x] = *p;
                }
            }
            return matrix;
        }
        /*
        // The following methods are not supported (the DataMatrix Reader doesn't call these methods)
        bool isCropSupported() const { return false; }
        zxing::Ref<LuminanceSource> crop(int left, int top, int width, int height) {}
        bool isRotateSupported() const { return false; }
        zxing::Ref<LuminanceSource> rotateCounterClockwise() {}
        */
    };


}
#endif //PRINTEDDOCUMENTLINKINGSYSTEM_OPENCVZXINGBRIDGEBITMAPSOURCE_H
