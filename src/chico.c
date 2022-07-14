/*

Chico: C/C++ CDK for building canisters on the Internet Computer

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ic0.h"


//
// This is the list of supported types.
// That is, these are the types that can be to and from a C/C++ canister
// 


uint8_t IDL_MAGIC[4] = {0x44, 0x49, 0x44, 0x4C};

//uint8_t IDL_TYPE_NULL = 0x7F;
uint8_t IDL_TYPE_BOOL = 0x7E;
// [IDL_MAGIC][00][01][IDL_TYPE_BOOL][00] for false
// [IDL_MAGIC][00][01][IDL_TYPE_BOOL][01] for true
// uint8_t IDL_TYPE_NAT = 0x7D;
uint8_t IDL_TYPE_int = 0x7C;
uint8_t IDL_TYPE_NAT8 = 0x7B;
uint8_t IDL_TYPE_NAT16 = 0x7A;
uint8_t IDL_TYPE_NAT32 = 0x79;
uint8_t IDL_TYPE_NAT64 = 0x78;
uint8_t IDL_TYPE_INT8 = 0x77;
uint8_t IDL_TYPE_INT16 = 0x76;
uint8_t IDL_TYPE_INT32 = 0x75;
uint8_t IDL_TYPE_INT64 = 0x74;
uint8_t IDL_TYPE_FLOAT32 = 0x73;
uint8_t IDL_TYPE_FLOAT64 = 0x72;
uint8_t IDL_TYPE_TEXT = 0x71;
//uint8_t IDL_TYPE_RESERVED = 0x70;
//uint8_t IDL_TYPE_EMPTY = 0x6F;
uint8_t IDL_TYPE_VEC = 0x6D;
uint8_t IDL_TYPE_RECORD = 0x6C;
uint8_t IDL_TYPE_PRINCIPAL = 0x68;



//
// Utility functions for encoding and decoding
//

void write_byte(uint8_t byte) {
  ic0_msg_reply_data_append((uint32_t)(&byte), 1);
}

void write_uleb128 (uint32_t x) {
  unsigned char buf[10];
  int bytes = 0;
  uint32_t len = x;
  do {
    buf[bytes] = x & 0x7fU;
    if (x >>= 7) buf[bytes] |= 0x80U;
    ++bytes;
  } while (x);
  write_byte((uint32_t)buf[0]);
  if ( len >= 256) {
    write_byte((uint32_t)buf[1]);
  }
  // we assume we don't need more than 256^2 sized buffers   
}


//
// Logging functions
//

void ic_log_message(const char *message) {
  ic0_debug_print((uint32_t)message, strlen(message));
}

//
//  Functions to read (input) data into a canister canister
//

void match_byte(const uint8_t *buf, size_t len, int off, uint8_t byte) {
  if (off >= len || buf[off] != byte) {
    trap("Invalid byte!");
  }
}

void match_magic(const uint8_t *buf, size_t len) {
  for (int i = 0; i < 4; i++) {
    match_byte(buf, len, i, IDL_MAGIC[i]);
  }
}

//
// reads for int/nat 8/16/32/64 bits
//

int8_t ic_reads_int8() {
  size_t len = (size_t)(ic0_msg_arg_data_size());
  uint8_t *buf = (uint8_t *)(malloc(len));
  ic0_msg_arg_data_copy((uint32_t)(buf), 0, (uint32_t)(len));
  match_magic(buf, len);
  match_byte(buf, len, 4, 0x00);
  match_byte(buf, len, 5, 0x01);
  match_byte(buf, len, 6, IDL_TYPE_INT8);
  int8_t result =  (int8_t)buf[7];  
  free(buf);
  return result;
}

int16_t ic_reads_int16() {
  size_t len = (size_t)(ic0_msg_arg_data_size());
  uint8_t *buf = (uint8_t *)(malloc(len));
  ic0_msg_arg_data_copy((uint32_t)(buf), 0, (uint32_t)(len));
  match_magic(buf, len);
  match_byte(buf, len, 4, 0x00);
  match_byte(buf, len, 5, 0x01);
  match_byte(buf, len, 6, IDL_TYPE_INT16);
  int16_t result =  (buf[7] | buf[8] << 8);
  free(buf);
  return result;
}

int32_t ic_reads_int32() {
  size_t len = (size_t)(ic0_msg_arg_data_size());
  uint8_t *buf = (uint8_t *)(malloc(len));
  ic0_msg_arg_data_copy((uint32_t)(buf), 0, (uint32_t)(len));
  match_magic(buf, len);
  match_byte(buf, len, 4, 0x00);
  match_byte(buf, len, 5, 0x01);
  match_byte(buf, len, 6, IDL_TYPE_INT32);
  int32_t result =  (buf[7] | buf[8] << 8 | buf[9] << 16 | buf[10] << 24);
  free(buf);
  return result;
}


int64_t ic_reads_int64() {
  size_t len = (size_t)(ic0_msg_arg_data_size());
  uint8_t *buf = (uint8_t *)(malloc(len));
  ic0_msg_arg_data_copy((uint32_t)(buf), 0, (uint32_t)(len));
  match_magic(buf, len);
  match_byte(buf, len, 4, 0x00);
  match_byte(buf, len, 5, 0x01);
  match_byte(buf, len, 6, IDL_TYPE_INT64);
  int64_t result =  (buf[7] | buf[8] << 8 | buf[9] << 16 | buf[10] << 24 | buf[11] <<32 | buf[12] << 40 | buf[13] << 48 | buf[14] << 56);
  free(buf);
  return result;
}


uint8_t ic_reads_nat8() {
  size_t len = (size_t)(ic0_msg_arg_data_size());
  uint8_t *buf = (uint8_t *)(malloc(len));
  ic0_msg_arg_data_copy((uint32_t)(buf), 0, (uint32_t)(len));
  match_magic(buf, len);
  match_byte(buf, len, 4, 0x00);
  match_byte(buf, len, 5, 0x01);
  match_byte(buf, len, 6, IDL_TYPE_NAT8);
  uint8_t result =  (uint8_t)buf[7];
  free(buf);
  return result;
}

uint16_t ic_reads_nat16() {
  size_t len = (size_t)(ic0_msg_arg_data_size());
  uint8_t *buf = (uint8_t *)(malloc(len));
  ic0_msg_arg_data_copy((uint32_t)(buf), 0, (uint32_t)(len));
  match_magic(buf, len);
  match_byte(buf, len, 4, 0x00);
  match_byte(buf, len, 5, 0x01);
  match_byte(buf, len, 6, IDL_TYPE_NAT16);
  uint16_t result =  (buf[7] | buf[8] << 8);
  free(buf);
  return result;
}

uint32_t ic_reads_nat32() {
  size_t len = (size_t)(ic0_msg_arg_data_size());
  uint8_t *buf = (uint8_t *)(malloc(len));
  ic0_msg_arg_data_copy((uint32_t)(buf), 0, (uint32_t)(len));
  match_magic(buf, len);
  match_byte(buf, len, 4, 0x00);
  match_byte(buf, len, 5, 0x01);
  match_byte(buf, len, 6, IDL_TYPE_NAT32);
  uint32_t result =  (buf[7] | buf[8] << 8 | buf[9] << 16 | buf[10] << 24);
  free(buf);
  return result;
}

uint64_t ic_reads_nat64() {
  size_t len = (size_t)(ic0_msg_arg_data_size());
  uint8_t *buf = (uint8_t *)(malloc(len));
  ic0_msg_arg_data_copy((uint32_t)(buf), 0, (uint32_t)(len));
  match_magic(buf, len);
  match_byte(buf, len, 4, 0x00);
  match_byte(buf, len, 5, 0x01);
  match_byte(buf, len, 6, IDL_TYPE_NAT64);
  uint64_t result =  (buf[7] | buf[8] << 8 | buf[9] << 16 | buf[10] << 24 | buf[11] <<32 | buf[12] << 40 | buf[13] << 48 | buf[14] << 56);
  free(buf);
  return result;
}


//
//  Functions to write (return) data from a canister
//


void write_magic() {
  ic0_msg_reply_data_append((uint32_t)(IDL_MAGIC), 4);
}

void write_nat16(uint16_t  val) {
  write_byte((uint8_t)val);
  write_byte((uint8_t)val>>8);
}

void write_nat32(uint32_t  val) {
  write_byte((uint8_t)val);
  write_byte((uint8_t)(val>>8));
  write_byte((uint8_t)(val>>16));
  write_byte((uint8_t)(val>>24));
}

void write_nat64(uint64_t  val) {
  write_byte((uint8_t)val);
  write_byte((uint8_t)(val>>8));
  write_byte((uint8_t)(val>>24));
  write_byte((uint8_t)(val>>32));
  write_byte((uint8_t)(val>>40));
  write_byte((uint8_t)(val>>48));
  write_byte((uint8_t)(val>>56));
}

void write_int16(int16_t  val) {
  write_byte(val & 0xFF);
  write_byte(val>>8 & 0xFF);
}

void write_int32(int32_t  val) {
  write_byte(val & 0xFF);
  write_byte((val>>8) & 0xFF);
  write_byte((val>>16) & 0xFF);
  write_byte((val>>24) & 0xFF);
}

void write_int64(int64_t  val) {
  write_byte(val & 0xFF);
  write_byte((val>>8) & 0xFF);
  write_byte((val>>16) & 0xFF);
  write_byte((val>>24) & 0xFF);
  write_byte((val>>32) & 0xFF);
  write_byte((val>>40) & 0xFF);
  write_byte((val>>48) & 0xFF);
  write_byte((val>>56) & 0xFF);
}

// should be renamed to ic_writes_byte
void write_return_byte(int x) {
  write_magic();
  write_byte(0x00);
  write_byte(0x01);
  write_byte(IDL_TYPE_int);
  write_byte((uint32_t)x);
  ic0_msg_reply();
}

// return a string (text)
void ic_writes_text(char *result){
  write_magic();
  write_byte(0x00);
  write_byte(0x01);
  write_byte(IDL_TYPE_TEXT);
  // write size of string
  write_uleb128(strlen(result));
  // write string
  for (int i = 0 ; i < strlen(result) ; i++) {
    write_byte(result[i]);
  }
  ic0_msg_reply();
}

// return a boolean value
void ic_writes_bool(_Bool val){
  write_magic();
  write_byte(0x00);
  write_byte(0x01);
  write_byte(IDL_TYPE_BOOL);
  if (val) {
    write_byte(0x01);
  }
  else {
    write_byte(0x00);
    }
  ic0_msg_reply();
}

// return int8_t
void ic_writes_int8(int8_t  val){
  write_magic();
  write_byte(0x00);
  write_byte(0x01);
  write_byte(IDL_TYPE_INT8);
  write_byte(val);
  ic0_msg_reply();
}

// return int_16                                                                                                                                                                                                                                                                                                  
void ic_writes_int16(int16_t  val){
  write_magic();
  write_byte(0x00);
  write_byte(0x01);
  write_byte(IDL_TYPE_INT16);
  write_int16(val);
  ic0_msg_reply();
}

// return int_32                                                                                                                                                                                                                                                                                                  
void ic_writes_int32(int32_t  val){
  write_magic();
  write_byte(0x00);
  write_byte(0x01);
  write_byte(IDL_TYPE_INT32);
  write_int32(val);
  ic0_msg_reply();
}

// return int_64                                                                                                                                                                                                                                                                                                  
void ic_writes_int64(int64_t  val){
  write_magic();
  write_byte(0x00);
  write_byte(0x01);
  write_byte(IDL_TYPE_INT64);
  write_int64(val);
  ic0_msg_reply();
}

// return uint8_t                                                                                                                                                                                                                                                                                                    
void ic_writes_nat8(uint8_t  val){
  write_magic();
  write_byte(0x00);
  write_byte(0x01);
  write_byte(IDL_TYPE_NAT8);
  write_byte(val);
  ic0_msg_reply();
}

// return uint_16                                                                                                                                                                                                                                                                                                    
void ic_writes_nat16(uint16_t  val){
  write_magic();
  write_byte(0x00);
  write_byte(0x01);
  write_byte(IDL_TYPE_NAT16);
  write_nat16(val);
  ic0_msg_reply();
}

// return uint_32                                                                                                                                                                                                                                                                                                    
void ic_writes_nat32(uint32_t  val){
  write_magic();
  write_byte(0x00);
  write_byte(0x01);
  write_byte(IDL_TYPE_NAT32);
  write_nat32(val);
  ic0_msg_reply();
}

// return uint_64                                                                                                                                                                                                                                                                                                    
void ic_writes_nat64(uint64_t  val){
  write_magic();
  write_byte(0x00);
  write_byte(0x01);
  write_byte(IDL_TYPE_NAT64);
  write_nat64(val);
  ic0_msg_reply();
}

