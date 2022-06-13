# Chico: a C/C++ CDK for building Internet Computer canisters
***
Chico allows C/C++ developers to build [Internet Computer](https://internetcomputer.org/) applications (canisters) using C and C++.

## Content
***
The repo contains a Dockerfile that can be used for development purposes. The Dockerfile contains all the necessary dependencies to get you started. it contains:
* the [LLVM](https://llvm.org/) compiler used to compile C/C++ code into wasm code
* the [WASI SDK](https://github.com/WebAssembly/wasi-sdk) that provides system libraries
* the latest dfx to build and deploy canisters
* Chico: a set of scripts and utilities for building C/C++ canisters

