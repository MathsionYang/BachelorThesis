#include "File.h"

namespace PDLS {

    bool File::isSupportedFile() const throw(PDLSException) {
        if(!bfs::exists(_path) || !bfs::is_regular_file(_path)) {
            throw FileNotFoundException(_path);
        } else {
            if(std::find(SUPPORTED_FILE_EXTENSIONS.begin(), SUPPORTED_FILE_EXTENSIONS.end(), _path.extension().string()) != SUPPORTED_FILE_EXTENSIONS.end()) {
                return true;
            }
        }
        throw UnsupportedFileException(_path.c_str());
    }

    bool File::isImageFile() const {
        return std::find(IMAGE_FILE_EXTENSIONS.begin(), IMAGE_FILE_EXTENSIONS.end(), _path.extension().string()) != IMAGE_FILE_EXTENSIONS.end();
    }

    bool File::isTextFile() const {
        return std::find(TEXT_FILE_EXTENSIONS.begin(), TEXT_FILE_EXTENSIONS.end(), _path.extension().string()) != TEXT_FILE_EXTENSIONS.end();
    }

    bool File::isPDFFile() const {
        return std::find(PDF_FILE_EXTENSIONS.begin(), PDF_FILE_EXTENSIONS.end(), _path.extension().string()) != PDF_FILE_EXTENSIONS.end();
    }

    bool File::isXMLFile() const {
        return std::find(XML_FILE_EXTENSIONS.begin(), XML_FILE_EXTENSIONS.end(), _path.extension().string()) != XML_FILE_EXTENSIONS.end();
    }

    bool File::isCryptoFile() const {
        return std::find(CRYPTO_FILE_EXTENSIONS.begin(), CRYPTO_FILE_EXTENSIONS.end(), _path.extension().string()) != CRYPTO_FILE_EXTENSIONS.end();
    }

    void File::load() throw(PDLSException) {
        if(isSupportedFile()) {
            //if stream is already set, delete it
            if(_stream)
                delete _stream;

            if(isTextFile()) {
                _type = FileType::TXT;
                _stream = new std::fstream(_path.string(), std::fstream::in);
                setTextualContent();
            } else if(isXMLFile()) {
                _type = FileType::XML;
                _stream = new std::fstream(_path.string(), std::fstream::in);
                setTextualContent();
            } else if(isImageFile()) {
                _type = FileType::IMG;
                _stream = new std::fstream(_path.string(), std::fstream::in | std::fstream::binary);
            } else if(isPDFFile()) {
                _type = FileType::PDF;
                _stream = new std::fstream(_path.string(), std::fstream::in | std::fstream::binary);
            } else if(isCryptoFile()) {
                _type = FileType::CRYPTO;
                _stream = new std::fstream(_path.string(), std::fstream::in);
                setTextualContent();
            }
        } else
            throw UnsupportedFileException(_path);
    }

    void File::setTextualContent() {//set textual content
        std::stringstream contentStream;
        contentStream << _stream->rdbuf();
        _content = contentStream.str();
    }

}
