#include "OCRTestApp.h"

void OCRTestApp::run(const std::string& pathToDoc) {

    Document* doc = new Document(pathToDoc);

    //extract document content
    Content* dc = _cem->extractContent(doc);
    doc->setContent(dc);

    //standardize document content
    NormalizedContent* sdc = _csm->normalizeContent(dc);
    doc->setNormalizedContent(sdc);


    //save content to disk
    std::stringstream out;
    out << doc->getPath().string() << ".standardizedOcrResult.txt";

    doc->saveNormalizedContentToDisk(out.str().c_str());

    delete doc;
}

