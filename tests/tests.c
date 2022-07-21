
/*
TESTS
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "ic0.h"
#include "chico.h"
#include "ic_vec.h"

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
  ic_log_message("start test");
  int16_t val = ic_reads_int16();
  ic_log_message("value is read");
  ic_writes_int16(val);
  ic_log_message("end of test");
}

void test_int32() WASM_EXPORT("canister_update test_int32");
void test_int32() {
  ic_log_message("start test");
  int32_t val = ic_reads_int32();
  ic_log_message("value is read");
  ic_writes_int32(val);
  ic_log_message("end of test");
}

void test_int64() WASM_EXPORT("canister_update test_int64");
void test_int64() {
  ic_log_message("start test");
  int64_t val = ic_reads_int64();
  ic_log_message("value is read");
  ic_writes_int64(val);
  ic_log_message("end of test");
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
  ic_log_message("start test");
  uint16_t val = ic_reads_nat16();
  ic_log_message("value is read");
  ic_writes_nat16(val);
  ic_log_message("end of test");
}

void test_nat32() WASM_EXPORT("canister_update test_nat32");
void test_nat32() {
  ic_log_message("start test");
  uint32_t val = ic_reads_nat32();
  ic_log_message("value is read");
  ic_writes_nat32(val);
  ic_log_message("end of test");
}

void test_nat64() WASM_EXPORT("canister_update test_nat64");
void test_nat64() {
  ic_log_message("start test");
  uint64_t val = ic_reads_nat64();
  ic_log_message("value is read");
  ic_writes_nat64(val);
  ic_log_message("end of test");
}

/*
 test bool
 */

void test_bool() WASM_EXPORT("canister_update test_bool");
void test_bool() {
  _Bool val = ic_reads_bool();
  ic_writes_bool(val);
}


/*
 test vec
 */

void test_vec_int64() WASM_EXPORT("canister_update test_vec_int64");
void test_vec_int64() {
  vector val= ic_reads_vec_int64(val);
  ic_writes_vec_int64(val);
}

void test_vec_nat64() WASM_EXPORT("canister_update test_vec_nat64");
void test_vec_nat64() {
  vector val= ic_reads_vec_nat64(val);
  ic_writes_vec_nat64(val);
}

void test_vec_int32() WASM_EXPORT("canister_update test_vec_int32");
void test_vec_int32() {
  vector val= ic_reads_vec_int32(val);
  ic_writes_vec_int32(val);
}

void test_vec_nat32() WASM_EXPORT("canister_update test_vec_nat32");
void test_vec_nat32() {
  vector val= ic_reads_vec_nat32(val);
  ic_writes_vec_nat32(val);
}

void test_vec_int16() WASM_EXPORT("canister_update test_vec_int16");
void test_vec_int16() {
  vector val= ic_reads_vec_int16(val);
  ic_writes_vec_int16(val);
}

void test_vec_nat16() WASM_EXPORT("canister_update test_vec_nat16");
void test_vec_nat16() {
  vector val= ic_reads_vec_nat16(val);
  ic_writes_vec_nat16(val);
}

void test_vec_int8() WASM_EXPORT("canister_update test_vec_int8");
void test_vec_int8() {
  vector val= ic_reads_vec_int8(val);
  ic_writes_vec_int8(val);
}

void test_vec_nat8() WASM_EXPORT("canister_update test_vec_nat8");
void test_vec_nat8() {
  vector val= ic_reads_vec_nat8(val);
  ic_writes_vec_nat8(val);
}


/*
  text text
*/

void test_text() WASM_EXPORT("canister_update test_text");
void test_text() {
  ic_log_message("test text");
  char *val= ic_reads_text();
  ic_writes_text(val);
}
