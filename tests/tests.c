
/*
TESTS
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ic0.h"
#include "chico.h"


/*
Tests
 */

void test_int8() WASM_EXPORT("canister_query test_int8");
void test_int8() {
  int8_t val = ic_reads_int8();
  ic_writes_int8(val);
}


void test_int16() WASM_EXPORT("canister_query test_int16");
void test_int16() {
  int16_t val = ic_reads_int16();
  ic_writes_int16(val);
}

void test_int32() WASM_EXPORT("canister_query test_int32");
void test_int32() {
  int32_t val = ic_reads_int32();
  ic_writes_int32(val);
}

void test_int64() WASM_EXPORT("canister_query test_int64");
void test_int64() {
  int64_t val = ic_reads_int64();
  ic_writes_int64(val);
}
