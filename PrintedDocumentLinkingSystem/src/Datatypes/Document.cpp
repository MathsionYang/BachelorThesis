#include "Document.h"

#include "Signature.h"
#include "Content.h"
#include "NormalizedContent.h"
#include "ContentHash.h"
#include "EnumTypes.h"

namespace PDLS {

    void Document::saveStringToDisk(const std::string& s, const bfs::path& out) const throw(PDLSException) {
        std::ofstream ofs(out.string(), std::ofstream::out);

        if(ofs.fail())
            throw SavingFileException(out.string());

        ofs << s;
        ofs.close();
    }

    void Document::saveContentToDisk(const bfs::path& out) const throw(PDLSException) {
        saveStringToDisk(_documentContent->getValue(), out);
    }

    void Document::saveNormalizedContentToDisk(const bfs::path& out) const throw(PDLSException) {
        saveStringToDisk(_standardizedContent->getValue(), out);
    }

    void Document::saveSignatureToDisk(const bfs::path& out) const throw(PDLSException) {
        saveStringToDisk(_documentSignature->getBase64Signature(), out);
    }

    void Document::saveContentHashToDisk(const bfs::path& out) const throw(PDLSException) {
        saveStringToDisk(_contentHash->getStringHash(), out);
    }

    Document::Document(bfs::path& pathToDoc) : File(pathToDoc),
                                               _documentContent(nullptr),
                                               _standardizedContent(nullptr),
                                               _contentHash(nullptr), _documentSignature(nullptr),
                                               _link(nullptr) {
        setTextFileContent();
    }

    Document::Document(const bfs::path& pathToDoc)  : File(pathToDoc),
                                                      _documentContent(nullptr),
                                                      _standardizedContent(nullptr),
                                                      _contentHash(nullptr),
                                                      _documentSignature(nullptr),
                                                      _link(nullptr) {
        setTextFileContent();
    }

    Document::Document(const std::string& pathToDoc) : File(pathToDoc),
                                                       _documentContent(nullptr),
                                                       _standardizedContent(nullptr),
                                                       _contentHash(nullptr),
                                                       _documentSignature(nullptr),
                                                       _link(nullptr) {
        setTextFileContent();
    }

    void Document::setTextFileContent() {
        if(_type == FileType::TXT) {
            //set file content as Document content
            std::stringstream contentStream;
            contentStream << _stream->rdbuf();
            _documentContent = new Content(this, contentStream.str());
        }
    }

    Document::~Document() {
        if(_documentContent) delete _documentContent;
        if(_standardizedContent) delete _standardizedContent;
        if(_contentHash) delete _contentHash;
        if(_documentSignature) delete _documentSignature;
    }
}

