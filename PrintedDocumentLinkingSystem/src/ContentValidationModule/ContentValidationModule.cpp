#include "ContentValidationModule.h"

#include "../Datatypes/EnumTypes.h"
#include "../ContentHashExtractionModule/ContentHashExtractionModule.h"
#include "../ContentExtractionModule/ContentExtractionModule.h"
#include "../ContentNormalizationModule/ContentNormalizationModule.h"
#include "../ContentHashGenerationModule/ContentHashGenerationModule.h"

#include <boost/algorithm/string.hpp>

namespace PDLS {

    /*
    ValidationState ContentValidationModule::validateContent(Document* inDoc, ContentHash* cHash) throw(PDLSException) {
        if(inDoc == nullptr)
            throw ContentValidationException("Input Document missing!");
        else if (cHash == nullptr)
            throw ContentValidationException("Input Content Hash missing!");

        ContentHash* validationContentHash = generateValidationContentHash(inDoc, cHash->getType(), cHash->getPrefix(), cHash->getPostfix());
        return (cHash->getStringHash() == validationContentHash->getStringHash()) ? ValidationState::VALID : ValidationState::INVALID;
    }

    ContentHash* ContentValidationModule::generateValidationContentHash(Document* inDoc, ContentHashType hT, const std::string& prefix, const std::string& postfix) const throw(PDLSException) {
        if(inDoc == nullptr)
            throw ContentValidationException("Input Document missing!");

        ContentExtractionModule* cem = ContentExtractionModule::getInstance();
        DocumentContent* content = cem->extractDocumentContent(inDoc);

        ContentNormalizationModule* csm = ContentNormalizationModule::getInstance();
        NormalizedDocumentContent* stdContent = csm->normalizeDocumentContent(content);

        ContentHashGenerationModule* chgm = ContentHashGenerationModule::getInstance();
        ContentHash* validationCHash = chgm->generateContentHash(stdContent, hT, prefix, postfix);

        return validationCHash;
    }
    */

    ValidationState ContentValidationModule::validateContent(ContentHash* chashA, ContentHash* chashB) throw(PDLSException) {
        return (chashA->getStringHash() == chashB->getStringHash()) ? ValidationState::VALID : ValidationState::INVALID;
    }


}
