#!/bin/bash

#
# Build HelloWorld canister and start alocal replica in the background
#

dfx new helloworld --frontend 
cd helloworld
dfx start --background 

dfx canister create helloworld_backend
dfx build 
dfx deploy

echo "Canister deployed"

cp ../helloworld.wasm .dfx/local/canisters/helloworld_backend/helloworld_backend.wasm
yes yes | dfx canister install -m reinstall helloworld_backend
dfx canister call helloworld_backend greet "$1"

echo "The end!"
