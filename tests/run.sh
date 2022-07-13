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
dfx canister call tests test_int8 '(1)' --type '(int8)'
dfx canister call tests test_int8 '(-1)' --type '(int8)'
dfx canister call tests test_int16 '(1)' --type '(int16)'
dfx canister call tests test_int16 '(-300)' --type '(int16)'
dfx canister call tests test_int32 '(300)' --type '(int32)'
dfx canister call tests test_int32 '(-1600)' --type '(int32)'
dfx canister call tests test_int64 '(300000)' --type '(int64)'
dfx canister call tests test_int64 '(-30000000)' --type '(int64)'

echo "The end!"
