
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
   char *val= ic_reads_text();
   len = strlen(val);
  // build response
  char s1[] = "Chico says hello to you ";
  char s2[] = " !";
  const size_t len1 = strlen(s1);
  const size_t len2 = strlen(s2);
  char *result_buf = malloc(strlen(s1) + len + strlen(s2) + 1);
  memcpy(result_buf, s1, len1);
  memcpy(result_buf + len1, val , len );
  memcpy(result_buf + len1 + len, s2, len2 + 1);
  ic_writes_text(result_buf);
  free(val);
  free(result_buf);
}
