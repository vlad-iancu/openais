#!/bin/bash

##########
###MAIN###
##########

SCRIPTS="$(cd "$(dirname "$0")" && pwd)"
PROJECT_DIR=$(dirname $SCRIPTS)
TEMP_DIR=$PROJECT_DIR/BuildDependencies/temp

mkdir -p $TEMP_DIR
touch $TEMP_DIR/Init.log


source $SCRIPTS/InstallBoost.sh