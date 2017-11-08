#include "SimplePythonImage2PDFConverter.h"
#include <python3.5/Python.h>

namespace PDLS {

    Document* SimplePythonImage2PDFConverter::convertImage2PDF(Document* img) throw(PDLSException) {
        std::cout << std::endl << "Starting Python img2pdf Converter to convert '" << img->getPath() << "' to a PDF-File!..." << std::endl << std::endl;

        //no error checking possible due to simple embedding..
        //see https://docs.python.org/3/extending/embedding.html -> pure embedding
        //for options to check error!
        Py_Initialize();

        std::stringstream pyCommand;
        //use img2pdf as lib in embedded python code (see https://gitlab.mister-muffin.de/josch/img2pdf)
        pyCommand << "import img2pdf\n";
        pyCommand << "pdf_bytes = img2pdf.convert('" << img->getPath().string() <<"', layout_fun=img2pdf.get_layout_fun((img2pdf.mm_to_pt(210),img2pdf.mm_to_pt(297)), None, None, None, None))\n";
        pyCommand << "file = open('" << img->getPath().string() << ".pdf" << "','wb')\n";
        pyCommand << "file.write(pdf_bytes)\n";

        PyRun_SimpleString(pyCommand.str().c_str());

        Py_Finalize();

        std::cout << std::endl << "...Done!'" << std::endl << std::endl;

        return new Document(bfs::path(img->getPath().string() + ".pdf"));
    }

}

