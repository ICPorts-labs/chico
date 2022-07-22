#!/bin/bash

# create the sqlite project
dfx new sqlite --no-frontend  
cd sqlite
dfx start --background 

# create the sqlite canister
dfx canister create sqlite_backend

dfx build 
dfx deploy

echo "Canister deployed"

# copy the sqlite.wasm and sqlite.did files
cp ../sqlite.wasm .dfx/local/canisters/sqlite_backend/sqlite_backend.wasm
cp ../sqlite.did  .dfx/local/canisters/sqlite_backend/sqlite_backend.did

# install canister
yes yes | dfx canister install -m reinstall sqlite_backend

# initialize DB
dfx canister call sqlite_backend sqlite_init

# create table
dfx canister call sqlite_backend sqlite_update  '("CREATE TABLE Cars(id int, name text, price int); INSERT INTO Cars VALUES(1, \"Audi\", 52642); INSERT INTO Cars VALUES(2, \"Mercedes\", 57127); INSERT INTO Cars VALUES(3, \"Skoda\", 9000); INSERT INTO Cars VALUES(4, \"Volvo\", 29000); INSERT INTO Cars VALUES(5, \"Bentley\", 350000); INSERT INTO Cars VALUES(6, \"Citroen\", 21000); INSERT INTO Cars VALUES(7, \"Hummer\", 41400); INSERT INTO Cars VALUES(8, \"Volkswagen\", 21600)")'

# query DB
dfx canister call sqlite_backend sqlite_query '("SELECT * FROM Cars")'


