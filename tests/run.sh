#!/bin/bash

#
# Build HelloWorld canister and start alocal replica in the background
#

dfx new tests
cd tests
dfx start --background 

dfx canister create tests_assets
dfx canister create tests

dfx build 
dfx deploy

echo "Canister deployed"

cp ../tests.wasm .dfx/local/canisters/tests/tests.wasm
cp ../tests.did .dfx/local/canisters/tests/tests.did
yes yes | dfx canister install -m reinstall tests
dfx canister call tests test_int8 '(1)'

echo "The end!"
