#include "TextLinkExtractor.h"

#include "../ContentExtractionModule/ContentExtractionModule.h"

#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>

namespace PDLS {

    Link* TextLinkExtractor::extractLink(Document* doc, LinkDescription* desc) throw(PDLSException) {
        if(!doc || !desc)
            throw NullPointerException("LDataLinkExtractionModule::extractLink");

        if(doc->getLink()) // if link is already set just return
            return doc->getLink();

        Content* dc = nullptr;
        if(!doc->getContent()) { //extract content if not done before
            dc = extractDocumentContent(doc);
            doc->setContent(dc);
        }
        else
            dc = doc->getContent();

        boost::regex expression{createLinkMatcher(desc)};
        //container to store regex matches
        boost::match_results<std::string::const_iterator> results;

        //search link pattern in doc content
        if (boost::regex_search(dc->getValue(), results, expression)) {
            if(results.size() > 1)
                throw TooManyLinksException(doc->getPath(), dc->getValue());

            //get result as string
            std::string linkString = results.str();

            //remove link from content
            std::string tmp(dc->getValue());
            boost::erase_all(tmp, linkString);
            dc->setValue(tmp);

            return new Link(linkString, desc);

        } else
            throw MissingLinkException(doc->getPath(), dc->getValue());

    }

    boost::regex&& TextLinkExtractor::createLinkMatcher(LinkDescription* desc) {
        //generate the link matcher string
        std::stringstream ss;
        ss << Link::__PREFIX__;
        ss << desc->getRegexMatcher();
        ss << Link::__POSTFIX__;
        return std::move(boost::regex(ss.str()));
    }

    Content* TextLinkExtractor::extractDocumentContent(Document* doc) {
        if(!doc)
            throw NullPointerException("RegexCHashExtractor::extractDocumentContent");

        ContentExtractionModule* cem = ContentExtractionModule::getInstance();
        Content* dc = cem->extractContent(doc);
        return dc;
    }

}

