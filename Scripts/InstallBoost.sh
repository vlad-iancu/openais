#!/bin/bash

#In order to run this script standalone the variables SCRIPTS, PROJECT_DIR and TEMP_DIR need to be set
BOOST_VERSION="1_78_0"

source $SCRIPTS/Common.sh

BOOST_ROOT=$PROJECT_DIR/BuildDependencies/boost

BOOST_SRC_URL="https://boostorg.jfrog.io/artifactory/main/release/$(echo $BOOST_VERSION | tr '_' '.')/source/boost_$BOOST_VERSION.tar.bz2"
BOOST_SRC="$TEMP_DIR/boost_$BOOST_VERSION.tar.bz2"

header "Install Boost"
mkdir -p $BOOST_ROOT
mkdir -p $TEMP_DIR


cd $TEMP_DIR
print "Downloading source"
wget $BOOST_SRC_URL 2>> $TEMP_DIR/Init.log 1>> $TEMP_DIR/Init.log

print "Inflating source"
tar --bzip2 -xf $BOOST_SRC

print "Configuring"
cd "$TEMP_DIR/boost_$BOOST_VERSION"

PWD=$(pwd)
$PWD/bootstrap.sh --prefix=$BOOST_ROOT 2>> $TEMP_DIR/Init.log 1>> $TEMP_DIR/Init.log


print "Compiling"
$PWD/b2 2>> $TEMP_DIR/Init.log 1>> $TEMP_DIR/Init.log


print "Installing"
$(pwd)/b2 install 2>> $TEMP_DIR/Init.log 1>> $TEMP_DIR/Init.log
success "Boost Successfully Installed"