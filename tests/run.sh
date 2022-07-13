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
dfx canister call tests test_int8 '(-1)'
dfx canister call tests test_int16 '(1)'
dfx canister call tests test_int16 '(-300)'
dfx canister call tests test_int32 '(300)'
dfx canister call tests test_int32 '(-1600)'
dfx canister call tests test_int64 '(300000)'
dfx canister call tests test_int64 '(-30000000)'

echo "The end!"
