#!/bin/bash

# Regular Colors
Black='\033[0;30m'        # Black
Red='\033[0;31m'          # Red
Green='\033[0;32m'        # Green
End='\033[m'
Yellow='\033[0;33m'       # Yellow
Blue='\033[0;34m'         # Blue
Purple='\033[1;35m'       # Purple
Cyan='\033[0;36m'         # Cyan
White='\033[0;37m'        # White

function header() {
    echo -e "$Purple$1$End"
}

function success(){
    echo -e "$Green$1$End"
}

function print() {
    echo "--$1--"
}