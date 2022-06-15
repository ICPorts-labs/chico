#!/bin/bash

#
# Build HelloWorld canister and start alocal replica in the background
#

dfx new helloworld
cd helloworld
dfx start --background 

dfx canister create helloworld_assets
dfx canister create helloworld

dfx build 
dfx deploy

echo "Canister deployed"

cp ../helloworld.wasm .dfx/local/canisters/helloworld/helloworld.wasm
yes yes | dfx canister install -m reinstall helloworld
dfx canister call helloworld greet "$1"

echo "The end!"
