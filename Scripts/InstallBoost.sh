#!/bin/bash

#In order to run this script standalone the variables SCRIPTS, PROJECT_DIR and TEMP_DIR need to be set
BOOST_VERSION="1_78_0"

BOOST_ROOT=$PROJECT_DIR/BuildDependencies/boost

BOOST_SRC_URL="https://boostorg.jfrog.io/artifactory/main/release/$(echo $BOOST_VERSION | tr '_' '.')/source/boost_$BOOST_VERSION.tar.bz2"
BOOST_SRC="$TEMP_DIR/boost_$BOOST_VERSION.tar.bz2"

header "Install Boost"
mkdir -p $BOOST_ROOT
mkdir -p $TEMP_DIR


cd $TEMP_DIR
print "Downloading source"
wget $BOOST_SRC_URL 

print "Inflating source"
tar --bzip2 -xf $BOOST_SRC

print "Configuring"
cd "$TEMP_DIR/boost_$BOOST_VERSION"

PWD=$(pwd)
$PWD/bootstrap.sh --prefix=$BOOST_ROOT 


print "Compiling"
CORES=$(grep ^cpu\\scores /proc/cpuinfo | uniq |  awk '{print $4}')
$PWD/b2 -j ${CORES} 


print "Installing"
$(pwd)/b2 install 
success "Boost Successfully Installed"