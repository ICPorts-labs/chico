#!/bin/bash

echo "WASI SDK PATH IS:"
echo ${WASI_SDK_PATH}
echo "CHICO PATH IS:"
echo ${CHICO_PATH}

SYSROOT=${WASI_SDK_PATH}/share/wasi-sysroot
WASI_LIBC=${SYSROOT}/lib/wasm32-wasi/libc.a


clang -c ${CHICO_PATH}/chico.c -o chico.o \
      -I ${CHICO_PATH} \
      -O3 --sysroot=${SYSROOT} --target=wasm32-wasi

clang -c helloworld.c -o helloworld.o \
      -I ${CHICO_PATH} \
      -O3 --sysroot=${SYSROOT} --target=wasm32-wasi

clang -c ${CHICO_PATH}/utils.c -o utils.o \
      -I ${CHICO_PATH} \
      -O3 --sysroot=${SYSROOT} --target=wasm32-wasi

wasm-ld helloworld.o chico.o utils.o -o helloworld.wasm \
	--demangle --allow-undefined --export-dynamic --no-entry  \
	${WASI_LIBC}

rm -f *.o

