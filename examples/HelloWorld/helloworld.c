
/*
 This is a simple Hello World!  canister 
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ic0.h"
#include "chico.h"


/*
 HelloWorld greet function
 */

void greet() WASM_EXPORT("canister_query greet");
void greet() {
  // read text input
  size_t len = (size_t)(ic0_msg_arg_data_size());
  uint8_t *buf = (uint8_t *)(malloc(len));
  ic0_msg_arg_data_copy((uint32_t)(buf), 0, (uint32_t)(len));
  match_magic(buf, len);
  match_byte(buf, len, 4, 0x00);
  match_byte(buf, len, 5, 0x01);
  match_byte(buf, len, 6, IDL_TYPE_text);
  int offset = 0;
  if (len < 256) {
    offset =8;
    }
  else {
    offset =9;
  }

  // build response
  char s1[] = "Chico says hello to you ";
  char s2[] = " !";
  const size_t len1 = strlen(s1);
  const size_t len2 = strlen(s2);
  char *result_buf = malloc(strlen(s1) + len + strlen(s2) + 1);
  memcpy(result_buf, s1, len1);
  memcpy(result_buf + len1, buf+offset , len );
  memcpy(result_buf + len1 + len -offset, s2, len2 + 1);
  ic_writes_text(result_buf);
  free(buf);
  free(result_buf);
}
