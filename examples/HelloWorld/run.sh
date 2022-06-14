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
cp ../helloworld.wasm .dfx/local/canisters/helloworld/helloworld.wasm
cp ../helloworld.did .dfx/local/canisters/helloworld/helloworld.did
dfx canister install -m reinstall helloworld
dfx canister call helloworld greet "ICP Fan"#!/bin/bash


