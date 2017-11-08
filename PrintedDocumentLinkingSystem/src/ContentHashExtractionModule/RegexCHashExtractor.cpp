#include "RegexCHashExtractor.h"
#include "../ContentNormalizationModule/ContentNormalizationModule.h"
#include "../ContentExtractionModule/ContentExtractionModule.h"
#include "../Datatypes/EnumTypes.h"
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>

namespace PDLS {

    ContentHash* RegexCHashExtractor::extractContentHash(Document* doc, const std::string& hashPrefix, const std::string& hashPostfix) {
        if(!doc)
            throw NullPointerException("RegexCHashExtractor::extractContentHash");

        Content* dc = nullptr;
        if(!doc->getContent()) {
            dc = extractDocumentContent(doc);
            doc->setContent(dc);
        }
        else
            dc = doc->getContent();

        boost::regex expression(hashPrefix + *_contentHashMatcherMap[_expectedHashType] + hashPostfix);
        boost::match_results<std::string::const_iterator> results; //container to store regex matches

        //search hash pattern
        if (boost::regex_search(dc->getValue(), results, expression)) {
            if(results.size() > 1)
                throw TooManyContentHashesException(doc->getPath());

            std::string contentHashString = results.str();

            //remove hash from content
            std::string tmp(dc->getValue());
            boost::erase_all(tmp, contentHashString);
            dc->setValue(tmp);

            return new ContentHash(_expectedHashType, contentHashString, hashPrefix, hashPostfix);

        } else
            throw MissingContentHashException(doc->getPath());

    }

    void RegexCHashExtractor::generateContentHashMatcherMap() {
        _contentHashMatcherMap.insert(std::make_pair(ContentHashType::MD5, new std::string("[A-Fa-f0-9]{32}")));
        _contentHashMatcherMap.insert(std::make_pair(ContentHashType::SHA1, new std::string("[A-Fa-f0-9]{40}")));
        _contentHashMatcherMap.insert(std::make_pair(ContentHashType::SHA224, new std::string("[A-Fa-f0-9]{56}")));
        _contentHashMatcherMap.insert(std::make_pair(ContentHashType::SHA256, new std::string("[A-Fa-f0-9]{64}")));
        _contentHashMatcherMap.insert(std::make_pair(ContentHashType::SHA384, new std::string("[A-Fa-f0-9]{96}")));
        _contentHashMatcherMap.insert(std::make_pair(ContentHashType::SHA512, new std::string("[A-Fa-f0-9]{128}")));
    }

    RegexCHashExtractor::RegexCHashExtractor(const ContentHashType& hT) : IContentHashExtractor(hT) {
        generateContentHashMatcherMap();
    }

    Content* RegexCHashExtractor::extractDocumentContent(Document* doc) {
        if(!doc)
            throw NullPointerException("RegexCHashExtractor::extractDocumentContent");

        ContentExtractionModule* cem = ContentExtractionModule::getInstance();
        Content* dc = cem->extractContent(doc);
        return dc;
    }

}

