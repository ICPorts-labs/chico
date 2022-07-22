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
  char *buf= ic_reads_text();
  int sql_len = strlen(buf);
  // display update message
  ic_log_message(buf);
 
  sqlite3_str *sql_stmt = sqlite3_str_new(db);
  sqlite3_str_append(sql_stmt,buf,sql_len );
  free(buf);
  char *sqlptr = sqlite3_str_finish(sql_stmt);
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


static int* write_back(sqlite3_str *query_result_buf , int argc, char **argv, 
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
  char *buf= ic_reads_text();
  int sql_len = strlen(buf);
  // display update message
  ic_log_message(buf);

  sqlite3_str *sql_stmt = sqlite3_str_new(db);
  sqlite3_str *query_result_buf = sqlite3_str_new(db);
  sqlite3_str_append(sql_stmt,buf,sql_len );
  free(buf);
  char *sqlptr = sqlite3_str_finish(sql_stmt);
  char* messageError=0;
  int rc = 0;
  if (db != NULL) {
    int rc = sqlite3_exec(db, sqlptr, write_back, query_result_buf, &messageError);
    char *queryptr = sqlite3_str_finish(query_result_buf);
    if (rc != SQLITE_OK ) {
     ic_writes_text("Query Failed :(");
    }
    else {
      ic_log_message("exec query is SQLITE_OK ");
      ic_writes_text(queryptr);
      sqlite3_free(queryptr);
    }
  }
  else {
    ic_writes_text("DB does not exist");
  }
  sqlite3_free(sqlptr);
}
