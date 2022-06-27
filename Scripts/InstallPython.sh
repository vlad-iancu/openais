#!/bin/bash
#This scripts compiles a specific version of python from source
PYTHON_VERSION="3.7.8"
PYTHON_MAJOR=$(echo "$PYTHON_VERSION" | sed -rn 's/([0-9]+)\.([0-9]+)\.([0-9]+)/\1/p')
PYTHON_MAJOR_MINOR=$(echo "$PYTHON_VERSION" | sed -rn 's/([0-9]+)\.([0-9]+)\.([0-9]+)/\1.\2/p')
INSTALLED_PYTHON3_EXEC=`which python3 `
INSTALLED_PYTHON_EXEC=`which python`
INSTALLED_PYTHON_VERSION=""
PYTHON_EXEC=""

function InstallFromSource() {
    
    echo "Install Python ($PYTHON_VERSION) in $PROJECT_DIR/BuildDependencies/Python"
    mkdir -p $TEMP_DIR
    PREV_DIR=$(pwd)
    cd $PROJECT_DIR/BuildDependencies/temp
    curl -O https://www.python.org/ftp/python/${PYTHON_VERSION}/Python-${PYTHON_VERSION}.tgz
    tar -xvzf Python-${PYTHON_VERSION}.tgz
    cd Python-${PYTHON_VERSION}
    ./configure \
      --prefix=$PROJECT_DIR/BuildDependencies/Python \
      --enable-shared \
      --enable-ipv6 \
      LDFLAGS=-Wl,-rpath=$PROJECT_DIR/BuildDependencies/Python/lib,--disable-new-dtags
    make
    make install
    cd $PREV_DIR
}

function WritePythonCmakeFile() {
  {
    local PYTHON_PACKAGE="Python${PYTHON_MAJOR}"
    if [ ! -z $1 ]
    then
    echo "set(${PYTHON_PACKAGE}_ROOT_DIR \"\${CMAKE_SOURCE_DIR}/BuildDependencies/Python\")"
    fi
    echo "find_package(${PYTHON_PACKAGE} ${PYTHON_VERSION} EXACT REQUIRED Development)"
    echo ""
    echo "set(PYTHON_LIBRARIES \${${PYTHON_PACKAGE}_LIBRARIES})"
    echo "set(PYTHON_INCLUDE_DIRS \${${PYTHON_PACKAGE}_INCLUDE_DIRS})"
    echo "set(PYTHON_CFLAGS_OTHER \${${PYTHON_PACKAGE}_CFLAGS_OTHER})"
  } > $PROJECT_DIR/Task/Python.cmake
  echo "Written Python cmake file at $PROJECT_DIR/openais/Python.cmake"
}

if [[ ! -z $INSTALLED_PYTHON3_EXEC ]]
  then
    PYTHON_EXEC=$INSTALLED_PYTHON3_EXEC
  else
  if [[ ! -z $INSTALLED_PYTHON_EXEC ]]
  then
    PYTHON_EXEC=$INSTALLED_PYTHON_EXEC
  else
    InstallFromSource
  fi
fi
INSTALLED_PYTHON_VERSION=`${PYTHON_EXEC} --version | awk '{print $2}'`
PS3="You have Python ${INSTALLED_PYTHON_VERSION} installed on your system, would you like to use that python installation or install one in this project? "
options=("Use Python ${INSTALLED_PYTHON_VERSION}" "Install one as a build dependency")
select opt in "${options[@]}"
do
  case $opt in
  "Use Python ${INSTALLED_PYTHON_VERSION}")
    PYTHON_VERSION=$INSTALLED_PYTHON_VERSION
    PYTHON_MAJOR=$(echo "$PYTHON_VERSION" | sed -rn 's/([0-9]+)\.([0-9]+)\.([0-9]+)/\1/p')
    PYTHON_MAJOR_MINOR=$(echo "$PYTHON_VERSION" | sed -rn 's/([0-9]+)\.([0-9]+)\.([0-9]+)/\1.\2/p')
    WritePythonCmakeFile
    break
  ;;
  "Install one as a build dependency")
    read -e -p "Enter the python version you want to use for this project (locally):" -i "$PYTHON_VERSION" PYTHON_VERSION
    PYTHON_MAJOR=$(echo "$PYTHON_VERSION" | sed -rn 's/([0-9]+)\.([0-9]+)\.([0-9]+)/\1/p')
    PYTHON_MAJOR_MINOR=$(echo "$PYTHON_VERSION" | sed -rn 's/([0-9]+)\.([0-9]+)\.([0-9]+)/\1.\2/p')
    InstallFromSource
    WritePythonCmakeFile "CUSTOM"
    break
  ;;
  esac
done
#pkg-config python${PYTHON_MAJOR}-embed --libs --cflags
