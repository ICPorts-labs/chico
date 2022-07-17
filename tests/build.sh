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

clang -c ${CHICO_PATH}/ic_vec.c -o ic_vec.o \
      -I ${CHICO_PATH} \
      -O3 --sysroot=${SYSROOT} --target=wasm32-wasi

clang -c ${CHICO_PATH}/utils.c -o utils.o \
      -I ${CHICO_PATH} \
      -O3 --sysroot=${SYSROOT} --target=wasm32-wasi

clang -c tests.c -o tests.o \
      -I ${CHICO_PATH} \
      -O3 --sysroot=${SYSROOT} --target=wasm32-wasi


wasm-ld tests.o chico.o ic_vec.o utils.o -o tests.wasm \
	--demangle --allow-undefined --export-dynamic --no-entry  \
	${WASI_LIBC}

rm -f *.o

