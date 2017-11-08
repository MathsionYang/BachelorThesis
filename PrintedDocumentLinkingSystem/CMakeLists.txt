cmake_minimum_required(VERSION 3.4)
project(PrintedDocumentLinkingSystem)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

option (ENABLE_TESTS
        "Enable the tests suite" ON)

include_directories(/usr/local/include/ /usr/include/)
link_directories(/usr/local/lib/ /usr/lib/ /usr/lib/x86_64-linux-gnu/)

#variable that contains third party libs that will be linkt to the project
set(THIRD_PARTY_LIBS "")

#boost
set(THIRD_PARTY_LIBS "boost_system" "boost_filesystem" "boost_regex" "boost_program_options" "${THIRD_PARTY_LIBS}")

#openCV
FIND_PACKAGE(OpenCV COMPONENTS core highgui imgproc REQUIRED)
set(THIRD_PARTY_LIBS ${OpenCV_LIBS} ${THIRD_PARTY_LIBS})

#openssl
set(THIRD_PARTY_LIBS "ssl" "crypto" "${THIRD_PARTY_LIBS}")

#tesseract
set(THIRD_PARTY_LIBS "tesseract" "lept" ${THIRD_PARTY_LIBS})

#ghostscript
set(THIRD_PARTY_LIBS "gs" ${THIRD_PARTY_LIBS})

#ipfs c++ api
set(THIRD_PARTY_LIBS "ipfs-api" "curl" ${THIRD_PARTY_LIBS})

#pugi xml lib
set(THIRD_PARTY_LIBS "pugixml" ${THIRD_PARTY_LIBS})

#python lib
set(THIRD_PARTY_LIBS "pthread" "dl" "util" "m" "python3.5m" ${THIRD_PARTY_LIBS})

#zxing c++ lib
set(THIRD_PARTY_LIBS "zxing" "${THIRD_PARTY_LIBS}")

set(DATATYPES_SOURCE_FILES #Datatype classes
        src/Datatypes/PDLSException.h
        src/Datatypes/Document.cpp
        src/Datatypes/File.cpp
        src/Datatypes/Link.cpp
        src/Datatypes/LinkDescription.cpp
        src/Datatypes/Content.h
        src/Datatypes/NormalizedContent.h
        src/Datatypes/ContentHash.cpp
        src/Datatypes/RSAKey.h
        src/Datatypes/Signature.h
        src/Datatypes/LinkingData.cpp
        src/Datatypes/X509Certificate.h
        src/Datatypes/EnumTypes.h
        )

set(UTILS_SOURCE_FILES #Utility Classes
        src/Util/IPDF2ImageConverter.h
        src/Util/IPDF2TextConverter.h
        src/Util/GhostScriptPDFManipulator.cpp
        src/Util/IImage2PDFConverter.h
        src/Util/SimplePythonImage2PDFConverter.cpp
        src/Util/IProvider.h
        src/Util/IPFSProvider.h
        src/Util/OpenCVZXingBridgeSource.h
        )

set(CEM_SOURCE_FILES #ContentExtractionModule
        src/ContentExtractionModule/ContentExtractionModule.cpp
        src/ContentExtractionModule/IExtractionStrategy.h
        src/ContentExtractionModule/PDFExtraction/ImagePDFExtractor.cpp
        src/ContentExtractionModule/PDFExtraction/TextPDFExtractor.cpp
        src/ContentExtractionModule/ImageExtraction/OCRExtractor.cpp
        src/ContentExtractionModule/XMLExtraction/XMLExtractor.cpp
        )

set(CNM_SOURCE_FILES #ContentNormalizationModule
        src/ContentNormalizationModule/ContentNormalizationModule.cpp
        src/ContentNormalizationModule/INormalizationAlgorithm.h
        src/ContentNormalizationModule/RegexNormalizationAlgorithm.cpp
        src/ContentNormalizationModule/RegexMatchReplacement.h
        )

set(CHGM_SOURCE_FILES #ContentHashGenerationModule
        src/ContentHashGenerationModule/ContentHashGenerationModule.cpp
        src/ContentHashGenerationModule/IContentHashGenerator.h
        src/ContentHashGenerationModule/OpenSSLContentHashGenerator.cpp
        )

set(SGM_SOURCE_FILES #SignatureGenerationModule
        src/SignatureGenerationModule/SignatureGenerationModule.cpp
        src/SignatureGenerationModule/ISignatureGenerator.h
        src/SignatureGenerationModule/OpenSSLSignatureGenerator.cpp
        )

set(DRM_SOURCE_FILES #DocumentLinkingModule
        src/DocumentLinkingModule/DocumentLinkingModule.cpp
        )

set(LIM_SOURCE_FILES #LinkInjectionModule
        src/LinkInjectionModule/LinkInjectionModule.cpp
        src/LinkInjectionModule/ILinkInjector.h
        src/LinkInjectionModule/XMLInjector.cpp
        src/LinkInjectionModule/ImageInjector.cpp
        src/LinkInjectionModule/PDFInjector.cpp
        src/LinkInjectionModule/TextInjector.cpp
        )

set(CHE_SOURCE_FILES #ContentHashExtractionModule
        src/ContentHashExtractionModule/ContentHashExtractionModule.cpp
        src/ContentHashExtractionModule/IContentHashExtractor.h
        src/ContentHashExtractionModule/RegexCHashExtractor.cpp
        )

set(LEM_SOURCE_FILES #LinkExtractionModule
        src/LinkExtractionModule/LinkExtractionModule.cpp
        src/LinkExtractionModule/ILinkExtractor.h
        src/LinkExtractionModule/TextLinkExtractor.cpp
        src/LinkExtractionModule/QRCodeLinkExtractor.cpp
        )

set(LDLM_SOURCE_FILES #LDataLoadingModule
        src/LDataLoadingModule/LDataLoadingModule.cpp
        )

set(CVM_SOURCE_FILES #ContentValidationModule
        src/ContentValidationModule/ContentValidationModule.cpp
        )

set(SVM_SOURCE_FILES #SignatureVerificationModule
        src/SignatureVerificationModule/SignatureVerificationModule.cpp
        src/SignatureVerificationModule/ISignatureValidator.h
        src/SignatureVerificationModule/ICertificateValidator.h
        src/SignatureVerificationModule/OpenSSLSelfSignedX509Validator.h
        src/SignatureVerificationModule/OpenSSLSignatureValidator.cpp
        )


set(NAYUKI_QR_CODE_GENERATOR_SOURCE_FILES #nayuki c++ QR Code Generator
        src/Util/nayukiQRCodeGen/QrCode.cpp
        src/Util/nayukiQRCodeGen/QrSegment.cpp
        src/Util/nayukiQRCodeGen/BitBuffer.cpp
        )

set(PDLS_SOURCE_FILES
        ${DATATYPES_SOURCE_FILES}
        ${UTILS_SOURCE_FILES}
        ${NAYUKI_QR_CODE_GENERATOR_SOURCE_FILES}

        ${CEM_SOURCE_FILES}
        ${CNM_SOURCE_FILES}
        ${CHGM_SOURCE_FILES}
        ${SGM_SOURCE_FILES}
        ${DRM_SOURCE_FILES}
        ${LIM_SOURCE_FILES}

        ${CHE_SOURCE_FILES}
        ${LEM_SOURCE_FILES}
        ${LDLM_SOURCE_FILES}
        ${CVM_SOURCE_FILES}
        ${SVM_SOURCE_FILES}


        src/PrintedDocumentLinkingSystem.cpp
        src/PDLS_main.cpp
        )

set(OCRTestApp_SOURCE_FILES
        ${DATATYPES_SOURCE_FILES}
        ${UTILS_SOURCE_FILES}

        ${CEM_SOURCE_FILES}
        ${CNM_SOURCE_FILES}

        src/OCRTestApp.cpp
        src/OCRTestApp_main.cpp
        )

add_executable(PrintedDocumentLinkingSystem ${PDLS_SOURCE_FILES})

target_link_libraries(PrintedDocumentLinkingSystem ${THIRD_PARTY_LIBS})

add_executable(OCRTestApp ${OCRTestApp_SOURCE_FILES})

target_link_libraries(OCRTestApp ${THIRD_PARTY_LIBS})