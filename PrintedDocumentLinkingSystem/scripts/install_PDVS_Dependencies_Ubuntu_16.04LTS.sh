#!/bin/bash

printInfo() {
	echo "This script will install all dependencies and libraries needed to compile PrintedDocumentVerificationSystem!"
	echo "It's only been tested on a Ubuntu 16.04 LTS!"
}

installCompilerDeps() {
	sudo apt update && sudo apt upgrade
	sudo apt install build-essential cmake git
}

install3rdPartyApps() {
	sudo apt install ghostscript-dbg tesseract-ocr-dev tesseract-ocr-deu* tesseract-ocr
	sudo -H pip install img2pdf #install python img2pdf module
}

installDevLibraries() {
	sudo apt install libcurl4-gnutls-dev libopencv*-dev libssl-dev libleptonica-dev libtesseract-dev libgs-dev libpugixml-dev 
}

install3rdPartyAPIs() {
#install nlohmann json for modern c++ api header (see git repo below)
	mkdir -v nlohmann
	curl -o ./nlohmann/json.hpp "https://raw.githubusercontent.com/nlohmann/json/develop/src/json.hpp"
	sudo mv -v ./nlohmann/ /usr/local/include/

	mkdir -v gitRepos
	cd gitRepos
	git clone "https://github.com/vasild/cpp-ipfs-api.git"
	cd cpp-ipfs-api
	cmake . -DCMAKE_BUILD_TYPE=Debug
	make
	sudo make install
	sudo ldconfig

	#building and installing openssl from source
	git clone "git://git.openssl.org/openssl.git"
	cd openssl 
	./config --debug 
	make -j4
	make -j4 test
	sudo make -j4 install
	sudo ldconfig 
	cd ..
}


printInfo

installCompilerDeps

install3rdPartyApps

installDevLibraries

install3rdPartyAPIs
