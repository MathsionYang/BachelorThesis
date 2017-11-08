#ifndef PRINTEDDOCUMENTVERIFICATIONSYSTEM_IPFSCLIENT_H
#define PRINTEDDOCUMENTVERIFICATIONSYSTEM_IPFSCLIENT_H

#include <ipfs/client.h>
#include <boost/algorithm/string.hpp>
#include "IProvider.h"
#include "../Datatypes/Link.h"

namespace PDLS {

    class IPFSProvider : public IProvider {

        std::string _apiHostName;
        unsigned int _apiPort;

        //see https://vasild.github.io/cpp-ipfs-api/
        ipfs::Client* _client;

        LinkDescription* _linkDescription;

        IPFSProvider() throw(PDLSException) : _apiHostName("localhost"), _apiPort(5001), _client(nullptr) {
            try {
                _client = new ipfs::Client(_apiHostName, _apiPort);
            } catch (const std::runtime_error& e) {
                throw IPFSConnectionException(e.what());
            } catch (...) {
                throw IPFSConnectionException("Cannot Connect to IPFS!");
            }

        }

        inline std::string addFile(const std::string& name, const std::string& content) {
            ipfs::Json result;
            try {
                _client->FilesAdd({{name, ipfs::http::FileUpload::Type::kFileContents, content}}, &result);
            } catch (const std::runtime_error& e) {
                throw IPFSConnectionException(e.what());
            } catch (...) {
                throw IPFSConnectionException("Cannot Connect to IPFS!");
            }
            std::string link = result.at(0)["hash"]; //ipfs hash of the uploaded file
            return ("/ipfs/" + link); //format of ipfs links: /ipfs/hash (better for humans to read -> normally only hash is used to access data)
        }

        inline std::string getTextFile(const std::string& link) {
            //remove /ipfs/ from link because ipfs accesses data only via hash
            std::string trimmedLink = boost::erase_all_copy(link, "/ipfs/");
            std::stringstream response;
            try {
                _client->FilesGet(trimmedLink, &response);
            } catch (const std::runtime_error& e) {
                throw IPFSConnectionException(e.what());
            } catch (...) {
                throw IPFSConnectionException("Cannot Connect to IPFS!");
            }
            return response.str(); //return content of the textual file
        }

    public:

        virtual Link* uploadLinkingData(LinkingData* ldata) throw(PDLSException) override {
            if(!ldata)
                throw NullPointerException("IPFSProvider::uploadLinkingData");

            std::cout << std::endl << "Uploading  Linking Data to IPFS!..." << std::endl << std::endl;

            std::string link = addFile(ldata->getDocumentName(), ldata->getJsonString());

            std::cout << std::endl << "...Done!'" << std::endl << std::endl;

            return new Link(link, this->getSupportedLinkDescription());
        }

        virtual LinkingData* downloadLinkingData(Link* link) throw(PDLSException) override {
            if(!link)
                throw NullPointerException("IPFSProvider::downloadLinkingData");
            if(link->getLinkDescription() != this->getSupportedLinkDescription())
                throw LinkMismatchException(link->getLinkAsString(), "IPFSProvider");

            std::cout << std::endl << "Downloading  Linking Data from IPFS!..." << std::endl << std::endl;

            std::string jsonLinkingData(getTextFile(link->getLinkAsString()));

            std::cout << std::endl << "...Done!'" << std::endl << std::endl;

            return new LinkingData(jsonLinkingData);
        }

        virtual LinkDescription* getSupportedLinkDescription() override {
            if(!_linkDescription)
                _linkDescription = new LinkDescription("IPFS", "/ipfs/Qm[A-Za-z0-9]{44}");
            return _linkDescription;
        }

        inline const std::string& getApiHostName() const {
            return _apiHostName;
        }

        inline void setApiHostName(const std::string& apiHostName) {
            _apiHostName = apiHostName;
            if(_client) delete _client;
            _client = new ipfs::Client(_apiHostName, _apiPort);
        }

        inline unsigned int getApiPort() const {
            return _apiPort;
        }

        inline void setApiPort(unsigned int apiPort) {
            _apiPort = apiPort;
            if(_client) delete _client;
            _client = new ipfs::Client(_apiHostName, _apiPort);
        }

        inline ipfs::Client* getClient() const {
            return _client;
        }

        static IPFSProvider* getInstance() {
            static IPFSProvider singleton;
            return &singleton;
        }

        IPFSProvider(const IPFSProvider&) = delete;
        void operator=(const IPFSProvider&) = delete;
    };

}

#endif //PRINTEDDOCUMENTVERIFICATIONSYSTEM_IPFSCLIENT_H
