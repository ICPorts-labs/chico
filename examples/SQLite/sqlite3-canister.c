/*

 This is a simple SQLITE canister 

 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include "ic0.h"
#include "chico.h"

/*                                                                                                                                     
 Global variables
 SQLITE
 
 We assume one DB, but we can create more than one.

 */

sqlite3 *db=NULL;



// call to create DB
void sqlite_init() WASM_EXPORT("canister_update sqlite_init");
void sqlite_init() {
  int rc=0;
  if (db == NULL) {
    ic_log_message("new table");
    rc = sqlite3_open_v2(":memory:",&db,SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE,"memvfs");
    if (rc != SQLITE_OK) {
      ic_log_message("open failed");
      write_return_byte(rc);
    }
    else {
      if (db==NULL) {
        ic_log_message("DB handle is NULL :(");
        write_return_byte(rc);
      }
      else {
      ic_log_message("DB is newly open");
      rc = sqlite3_exec(db, "pragma journal_mode = OFF", NULL, NULL, NULL);
      write_return_byte(rc);
      }
    }
  }
  else
    {
      ic_log_message("DB is already open");
      write_return_byte(88);
    }
}
    

// call to update DB
void sqlite_update() WASM_EXPORT("canister_update sqlite_update");
void sqlite_update() {
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
  ic_log_message(buf+offset);
  int sql_len = len - offset;
  sqlite3_str *sql_stmt = sqlite3_str_new(db);
  sqlite3_str_append(sql_stmt,buf+offset,sql_len );
  free(buf);
  const char *sqlptr = sqlite3_str_finish(sql_stmt);
  char* messageError=0;
  int rc = 0;
  if (db == NULL) {
    ic_log_message("please call sqlite_init before sending queries to the DB");
    write_return_byte(1);
  }
  else {
    ic_log_message("Updating DB");
    ic_log_message(sqlptr);
    rc = sqlite3_exec(db, sqlptr , 0, 0, &messageError);
    ic_log_message(messageError);
    write_return_byte(rc);
  }
  sqlite3_free(sqlptr);
}


int write_back(sqlite3_str *query_result_buf , int argc, char **argv, 
                    char **azColName) {
  for (int i = 0; i < argc; i++) {
    sqlite3_str_appendall(query_result_buf, azColName[i]);
    sqlite3_str_appendall(query_result_buf, " = ");
    if (argv[i]) {
      sqlite3_str_appendall(query_result_buf, argv[i]);
    }
    else {
      sqlite3_str_appendall(query_result_buf, " NULL ");
    }
    sqlite3_str_appendall(query_result_buf, "\n");
  }
  return 0;
}

// call to query DB
void sqlite_query() WASM_EXPORT("canister_query sqlite_query");
void sqlite_query() {
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
  ic_log_message(buf+offset);
  int sql_len = len - offset;
  sqlite3_str *sql_stmt = sqlite3_str_new(db);
  sqlite3_str *query_result_buf = sqlite3_str_new(db);
  sqlite3_str_append(sql_stmt,buf+offset,sql_len );
  free(buf);
  char *sqlptr = sqlite3_str_finish(sql_stmt);
  char* messageError=0;
  int rc = 0;
  if (db != NULL) {
    int rc = sqlite3_exec(db, sqlptr, write_back, query_result_buf, &messageError);
    char *queryptr = sqlite3_str_finish(query_result_buf);
    if (rc != SQLITE_OK ) {
     write_return_text("Query Failed :(");
    }
    else {
      ic_log_message("exec query is SQLITE_OK ");
      write_return_text(queryptr);
      sqlite3_free(queryptr);
    }
  }
  else {
    write_return_text("DB does not exist");
  }
  sqlite3_free(sqlptr);
}
