
DOXYGEN_VERSION="1_9_3"

source $SCRIPTS/Common.sh

cd $PROJECT_DIR/BuildDependencies

header "Install Doxygen"
print "Downloading source"
git clone https://github.com/doxygen/doxygen.git 2>> $TEMP_DIR/Init.log 1>> $TEMP_DIR/Init.log
git checkout tags/Release_${DOXYGEN_VERSION} 2>> $TEMP_DIR/Init.log 1>> $TEMP_DIR/Init.log
print "Configuring"
mkdir -p doxygen/build
mkdir -p doxygen/build/target
cd doxygen/build
cmake -G "Unix Makefiles" -DCMAKE_INSTALL_PREFIX=target .. 2>> $TEMP_DIR/Init.log 1>> $TEMP_DIR/Init.log
print "Compiling"
CORES=$(grep ^cpu\\scores /proc/cpuinfo | uniq |  awk '{print $4}')
make -j${CORES} 2>> $TEMP_DIR/Init.log 1>> $TEMP_DIR/Init.log
print "Installing"
make install 2>> $TEMP_DIR/Init.log 1>> $TEMP_DIR/Init.log
success "Doxygen Successfully Installed"
cd $PROJECT_DIR
BuildDependencies/doxygen/build/target/bin/doxygen -g
cp $PROJECT_DIR/Scripts/Resources/Doxyfile.in $PROJECT_DIR