#!/bin/bash

echo "WASI SDK PATH IS:"
echo ${WASI_SDK_PATH}
echo "CHICO PATH IS:"
echo ${CHICO_PATH}

SYSROOT=${WASI_SDK_PATH}/share/wasi-sysroot
WASI_LIBC=${SYSROOT}/lib/wasm32-wasi/libc.a

echo "SYSROOT PATH IS:"
echo ${SYSROOT}

clang -c ${CHICO_PATH}/chico.c -o chico.o \
      -I ${CHICO_PATH} \
      -O3 --sysroot=${SYSROOT} --target=wasm32-wasi

clang -c ${CHICO_PATH}/unreachable.c -o unreachable.o \
      -I ${CHICO_PATH} \
      -O3 --sysroot=${SYSROOT} --target=wasm32-wasi

clang -c sqlite3.c -o sqlite3.o \
      -DSQLITE_OS_OTHER=1 \
      -DSQLITE_OMIT_PROGRESS_CALLBACK \
      -DSQLITE_OMIT_XFER_OPT\
      -DHAVE_READLINE=0 -DHAVE_EDITLINE=0 -DSQLITE_OMIT_LOAD_EXTENSION \
      -DSQLITE_OMIT_SHARED_CACHE=1 \
      -DSQLITE_ENABLE_MEMORY_MANAGEMENT=1 \
      -DSQLITE_ENABLE_MEMSYS3=1 \
      -DSQLITE_TEMP_STORE=3 \
      -DSQLITE_OMIT_DEPRECATED=1 \
      -DSQLITE_MAX_EXPR_DEPTH=0 \
      -DSQLITE_THREADSAFE=0 \
      -DSQLITE_OMIT_TRACE=1 -DSQLITE_OMIT_RANDOMNESS=1 \
      -DNDEBUG \
      -DSQLITE_CORE=1 \
      -O3 --sysroot=${SYSROOT} --target=wasm32-wasi

clang -c memvfs.c  -o memvfs.o \
      -O3 --sysroot=${SYSROOT} --target=wasm32-wasi \
      -I.

clang -c sqlite_os_init.c -o sqlite_os_init.o \
      -O3 --sysroot=${SYSROOT} --target=wasm32-wasi

clang -c sqlite3-canister.c  -o sqlite3-canister.o \
      -O3 --sysroot=${SYSROOT} --target=wasm32-wasi \
      -I ${CHICO_PATH} \
      -I.

wasm-ld sqlite3-canister.o memvfs.o sqlite_os_init.o sqlite3.o unreachable.o utils.o -o sqlite.wasm \
	--demangle --allow-undefined --export-dynamic --no-entry  \
	${WASI_LIBC}

rm -f *.o

