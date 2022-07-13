
/*
TESTS
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ic0.h"
#include "chico.h"


/*
Tests int
 */

void test_int8() WASM_EXPORT("canister_update test_int8");
void test_int8() {
  ic_log_message("start test");
  int8_t val = ic_reads_int8();
  ic_log_message("value is read");
  ic_writes_int8(val);
  ic_log_message("end of test");
}


void test_int16() WASM_EXPORT("canister_update test_int16");
void test_int16() {
  int16_t val = ic_reads_int16();
  ic_writes_int16(val);
}

void test_int32() WASM_EXPORT("canister_update test_int32");
void test_int32() {
  int32_t val = ic_reads_int32();
  ic_writes_int32(val);
}

void test_int64() WASM_EXPORT("canister_update test_int64");
void test_int64() {
  int64_t val = ic_reads_int64();
  ic_writes_int64(val);
}

/*
Tests nat
 */

void test_nat8() WASM_EXPORT("canister_update test_nat8");
void test_nat8() {
  ic_log_message("start test");
  uint8_t val = ic_reads_nat8();
  ic_log_message("value is read");
  ic_writes_nat8(val);
  ic_log_message("end of test");
}


void test_nat16() WASM_EXPORT("canister_update test_nat16");
void test_nat16() {
  uint16_t val = ic_reads_nat16();
  ic_writes_nat16(val);
}

void test_nat32() WASM_EXPORT("canister_update test_nat32");
void test_nat32() {
  uint32_t val = ic_reads_nat32();
  ic_writes_nat32(val);
}

void test_nat64() WASM_EXPORT("canister_update test_nat64");
void test_nat64() {
  uint64_t val = ic_reads_nat64();
  ic_writes_nat64(val);
}
