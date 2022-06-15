#!/bin/bash
DOXYGEN_VERSION="1_9_3"

cd $PROJECT_DIR/BuildDependencies

header "Install Doxygen"
print "Downloading source"
git clone https://github.com/doxygen/doxygen.git 
git checkout tags/Release_${DOXYGEN_VERSION} 
print "Configuring"
mkdir -p doxygen/build
mkdir -p doxygen/build/target
cd doxygen/build
cmake -G "Unix Makefiles" -DCMAKE_INSTALL_PREFIX=target .. 
print "Compiling"
CORES=$(grep ^cpu\\scores /proc/cpuinfo | uniq |  awk '{print $4}')
make -j${CORES} 
print "Installing"
make install 
success "Doxygen Successfully Installed"
cd $PROJECT_DIR
BuildDependencies/doxygen/build/target/bin/doxygen -g 
cp $PROJECT_DIR/Scripts/Resources/Doxyfile.in $PROJECT_DIR 