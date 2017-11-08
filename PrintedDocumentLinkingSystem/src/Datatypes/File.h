#ifndef PRINTEDDOCUMENTVERIFICATIONSYSTEM_FILE_H
#define PRINTEDDOCUMENTVERIFICATIONSYSTEM_FILE_H

#include <fstream>
#include <string>
#include <set>

#include <boost/filesystem.hpp>

#include "PDLSException.h"
#include "EnumTypes.h"

namespace PDLS {

    namespace bfs = boost::filesystem;

    class File {
    public:
        const std::set<std::string> SUPPORTED_FILE_EXTENSIONS {".tif", ".tiff", ".bmp", ".jpeg", ".jpg", ".png", ".pdf", ".xml", ".fo", ".txt", ".pem"};
        const std::set<std::string> IMAGE_FILE_EXTENSIONS {".tif", ".tiff", ".bmp", ".jpeg", ".jpg", ".png"};
        const std::set<std::string> PDF_FILE_EXTENSIONS {".pdf"};
        const std::set<std::string> TEXT_FILE_EXTENSIONS {".txt"};
        const std::set<std::string> XML_FILE_EXTENSIONS {".xml", ".fo"}; //.fo = .xsl.fo
        const std::set<std::string> CRYPTO_FILE_EXTENSIONS {".pem"}; //.fo = .xsl.fo

    protected:
        bfs::path _path;
        std::fstream* _stream;
        std::string _content;
        FileType _type;

        bool isSupportedFile() const throw(PDLSException);
        bool isImageFile() const;
        bool isTextFile() const;
        bool isXMLFile() const;
        bool isPDFFile() const;
        bool isCryptoFile() const;
        void load() throw(PDLSException);
        void setTextualContent();

    public:
        File(bfs::path& p) : _path(p), _stream(nullptr) { load(); }
        File(bfs::path&& p) : _path(p), _stream(nullptr) { load(); }
        File(const bfs::path& p) : _path(p), _stream(nullptr) { load(); }
        File(const bfs::path& p, std::fstream* stream) : _path(p), _stream(stream) { }
        virtual ~File() { if(_stream) delete _stream; }

        inline std::fstream* getStream() {
            if(!_stream->is_open())
                load();
            _stream->clear();
            _stream->seekg(0, std::ios::beg);
            return _stream;
        }

        const std::string& getContentAsString() const {
            return _content;
        }

        inline void setStream(std::fstream* stream) {
            _stream = stream;
        }

        inline FileType getType() const {
            return _type;
        }

        inline const bfs::path& getPath() const {
            return _path;
        }

        inline void removeFromDisk() {
            if(_stream->is_open())
            _stream->close();
            bfs::remove(_path); //remove the converted file from disk
        }

        inline void rename(bfs::path p) {
            if(_stream->is_open())
                _stream->close();
            bfs::rename(_path, p);
            _path = p;
            load();
        }

        inline bool operator==(const File& rhs) {
            return _path == rhs._path;
        }

        inline bool operator!=(const File& rhs) {
            return !operator==(rhs);
        }
    };

}

#endif //PRINTEDDOCUMENTVERIFICATIONSYSTEM_FILE_H
