#
# Dockerfile for the development of Internet Computer canisters using CXX CDK
#
# (c) 2022
#
# ICPORTS Labs
#
#

FROM ubuntu

MAINTAINER ICPORTS <info-icports>

#
# Update
#

RUN apt-get update && apt-get upgrade -y
RUN apt-get update

#
# Install utilities
#

RUN apt-get install curl -y
RUN apt-get install git -y

#
# Install LLVM
#

RUN apt-get install clang lldb lld -y


#
# Install DFX
#

RUN sh -ci "$(curl -fsSL https://smartcontracts.org/install.sh)"
RUN dfx --version

#
# Install and wasi-sdk
#

RUN apt-get install wget

ENV WASI_VERSION "14"
ENV WASI_VERSION_FULL "$WASI_VERSION.0"
RUN wget https://github.com/WebAssembly/wasi-sdk/releases/download/wasi-sdk-${WASI_VERSION}/wasi-sdk-${WASI_VERSION_FULL}-linux.tar.gz
RUN tar xvf wasi-sdk-${WASI_VERSION_FULL}-linux.tar.gz


#
# set SDK env var 
#

ENV WASI_SDK_PATH "/wasi-sdk-${WASI_VERSION_FULL}-linu"
RUN echo $WASI_SDK_PATH

#
# Download chico and set working directory to chico
#

RUN git clone https://github.com/ICPorts-labs/chico.git
WORKDIR chico
ENV CHICO_PATH "/chico"