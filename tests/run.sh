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
dfx canister call tests test_int8 '(1 : int8 )' --type idl
dfx canister call tests test_int8 '(-1 : int8) ' --type idl
dfx canister call tests test_int16 '(1 : int16)' --type idl
dfx canister call tests test_int16 '(-300 : int32)' --type idl
dfx canister call tests test_int32 '(300 : int32)' --type idl
dfx canister call tests test_int32 '(-1600 : int32)' --type idl
dfx canister call tests test_int64 '(300000 : int64)' --type idl
dfx canister call tests test_int64 '(-30000000 : int64)' --type idl

dfx canister call tests test_nat8 '(1 : nat8)' --type idl
dfx canister call tests test_nat8 '(100 : nat8)' --type idl
dfx canister call tests test_nat16 '(1 : nat16)' --type idl
dfx canister call tests test_nat16 '(100 : nat16)' --type idl
dfx canister call tests test_nat32 '(1 : nat32)' --type idl
dfx canister call tests test_nat32 '(100 : nat32)' --type idl
dfx canister call tests test_nat64 '(1 : nat64)' --type idl
dfx canister call tests test_nat64 '(100 : nat64)' --type idl


echo "The end!"
