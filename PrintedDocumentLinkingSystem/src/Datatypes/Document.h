#ifndef CONTENTEXTRACTIONMODULE_DOCUMENT_H
#define CONTENTEXTRACTIONMODULE_DOCUMENT_H

#include "File.h"
#include "../Datatypes/Link.h"

namespace PDLS {

    //forward declarations
    class Content;
    class NormalizedContent;
    class ContentHash;
    class Signature;
    class Link;

    class Document : public File {
        void saveStringToDisk(const std::string& s, const bfs::path& out) const throw(PDLSException);
        void setTextFileContent();

    protected:
        Content* _documentContent;
        NormalizedContent* _standardizedContent;
        ContentHash* _contentHash;
        Signature* _documentSignature;
        Link* _link;

    public:

        Document(bfs::path& pathToDoc);
        Document(const bfs::path& pathToDoc);
        Document(const std::string& pathToDoc);
        virtual ~Document();

        void saveContentToDisk(const bfs::path& out) const throw(PDLSException);

        void saveNormalizedContentToDisk(const bfs::path& out) const throw(PDLSException);

        void saveSignatureToDisk(const bfs::path& out) const throw(PDLSException);

        void saveContentHashToDisk(const bfs::path& out) const throw(PDLSException);

        inline Content* getContent() const {
            return _documentContent;
        }

        inline void setContent(Content* documentContent) {
            _documentContent = documentContent;
        }

        inline NormalizedContent* getNormalizedContent() const {
            return _standardizedContent;
        }

        inline void setNormalizedContent(NormalizedContent* standardizedContent) {
            _standardizedContent = standardizedContent;
        }

        inline ContentHash* getContentHash() const {
            return _contentHash;
        }

        inline void setContentHash(ContentHash* contentHash) {
            _contentHash = contentHash;
        }

        inline Signature* getSignature() const {
            return _documentSignature;
        }

        inline void setSignature(Signature* documentSignature) {
            _documentSignature = documentSignature;
        }

        inline Link* getLink() const {
            return _link;
        }

        inline void setLink(Link* link) {
            _link = link;
        }
    };

}

#endif //CONTENTEXTRACTIONMODULE_DOCUMENT_H
