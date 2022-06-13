/*

Chico: C/C++ CDK for building canisters on the Internet Computer

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ic0.h"

uint8_t IDL_MAGIC[4] = {0x44, 0x49, 0x44, 0x4C};
uint8_t IDL_TYPE_int = 0x7C;
uint8_t IDL_TYPE_text = 0x71;

void write_magic() {
  ic0_msg_reply_data_append((uint32_t)(IDL_MAGIC), 4);
}

void write_byte(uint8_t byte) {
  ic0_msg_reply_data_append((uint32_t)(&byte), 1);
}

void write_return_byte(int x) {
  write_magic();
  write_byte(0x00);
  write_byte(0x01);
  write_byte(IDL_TYPE_int);
  write_byte((uint32_t)x);
  ic0_msg_reply();
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

void ic_writes_text(char *result){
  write_magic();
  write_byte(0x00);
  write_byte(0x01);
  write_byte(IDL_TYPE_text);
  // write size of string
  write_uleb128(strlen(result));
  // write string
  for (int i = 0 ; i < strlen(result) ; i++) {
    write_byte(result[i]);
  }
  ic0_msg_reply();
}

void ic_log_message(const char *message) {
  ic0_debug_print((uint32_t)message, strlen(message));
}

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
