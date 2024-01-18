FROM ubuntu:22.04

RUN apt-get update
RUN apt install -y wget
RUN apt install -y bzip2
RUN apt install -y build-essential
RUN apt install -y cmake
RUN apt install -y doxygen
RUN apt install -y git
RUN apt install -y m4
RUN apt install protobuf-compiler
RUN apt install -y python3.10-dev
RUN cd /tmp && \
    wget https://boostorg.jfrog.io/artifactory/main/release/1.82.0/source/boost_1_82_0.tar.bz2 && \
    tar --bzip2 -xf boost_1_82_0.tar.bz2 && \
    cd boost_1_82_0 && ./bootstrap.sh && ./b2 install

ENTRYPOINT [ "/bin/bash" ]
