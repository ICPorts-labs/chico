#include <stdio.h>
#include <stdlib.h>

//#include "vector.h"
#include "ic_vec.h"       
#include <chico.h>
#include "ic0.h"

void vector_init(vector *v)
{
    v->capacity = VECTOR_INIT_CAPACITY;
    v->total = 0;
    v->items = malloc(sizeof(void *) * v->capacity);
}

int vector_total(vector *v)
{
    return v->total;
}

static void vector_resize(vector *v, int capacity)
{
    #ifdef DEBUG_ON
    printf("vector_resize: %d to %d\n", v->capacity, capacity);
    #endif

    void **items = realloc(v->items, sizeof(void *) * capacity);
    if (items) {
        v->items = items;
        v->capacity = capacity;
    }
}

void vector_add(vector *v, void *item)
{
    if (v->capacity == v->total)
        vector_resize(v, v->capacity * 2);
    v->items[v->total++] = item;
}

void vector_set(vector *v, int index, void *item)
{
    if (index >= 0 && index < v->total)
        v->items[index] = item;
}

void *vector_get(vector *v, int index)
{
    if (index >= 0 && index < v->total)
        return v->items[index];
    return NULL;
}

void vector_delete(vector *v, int index)
{
    if (index < 0 || index >= v->total)
        return;

    v->items[index] = NULL;

    for (int i = index; i < v->total - 1; i++) {
        v->items[i] = v->items[i + 1];
        v->items[i + 1] = NULL;
    }

    v->total--;

    if (v->total > 0 && v->total == v->capacity / 4)
        vector_resize(v, v->capacity / 2);
}

void vector_free(vector *v)
{
    free(v->items);
}

//
// reading and writing vec
//

// int64
vector ic_reads_vec_int64(vector v){
  vector_init(&v);
  size_t len = (size_t)(ic0_msg_arg_data_size());
  uint8_t *buf = (uint8_t *)(malloc(len));
  ic0_msg_arg_data_copy((uint32_t)(buf), 0, (uint32_t)(len));
  match_magic(buf, len);
  match_byte(buf, len, 4, 0x01);
  match_byte(buf, len, 5, IDL_TYPE_VEC);
  match_byte(buf, len, 6, IDL_TYPE_INT64);
  match_byte(buf, len, 7, 0x01);
  match_byte(buf, len, 8, 0x00);
  uint8_t budget_var=1;
  uint8_t *budget;
  budget = &budget_var;
  uint32_t vec_length= read_uleb128(buf,9,budget);
  int64_t result = 0;
  for (uint32_t i=0 ; i< vec_length; i=i+1) {
    uint32_t offset= i*sizeof(int64_t) + *budget;
    result =  ((int64_t)buf[9 + offset] | (int64_t)buf[10 + offset] << 8 | (int64_t)buf[11 + offset] << 16 | (int64_t)buf[12 + offset] << 24 | (int64_t)buf[13 + offset] <<32 | (int64_t)buf[14 + offset] << 40 | (int64_t)buf[15 + offset] << 48 | (int64_t)buf[16 + offset] << 56);
    int64_t *ptr = (int64_t *)malloc(sizeof(int64_t));
    ptr[0]=result;
    vector_add(&v,ptr);
  }
  free(buf);
  return v;
}

void ic_writes_vec_int64(vector v){
  write_magic();
  write_byte(0x01);
  write_byte(IDL_TYPE_VEC);
  write_byte(IDL_TYPE_INT64);
  write_byte(0x01);
  write_byte(0x00);
  write_uleb128(vector_total(&v));
  int i =0;
  for (i = 0; i < vector_total(&v); i++)
    {
      int64_t *val = vector_get(&v, i);
      write_int64(val[0]);
    }
  ic0_msg_reply();
}

// nat64
vector ic_reads_vec_nat64(vector v){
  vector_init(&v);
  size_t len = (size_t)(ic0_msg_arg_data_size());
  uint8_t *buf = (uint8_t *)(malloc(len));
  ic0_msg_arg_data_copy((uint32_t)(buf), 0, (uint32_t)(len));
  match_magic(buf, len);
  match_byte(buf, len, 4, 0x01);
  match_byte(buf, len, 5, IDL_TYPE_VEC);
  match_byte(buf, len, 6, IDL_TYPE_NAT64);
  match_byte(buf, len, 7, 0x01);
  match_byte(buf, len, 8, 0x00);
  uint8_t budget_var=1;
  uint8_t *budget;
  budget = &budget_var;
  uint32_t vec_length= read_uleb128(buf,9,budget);
  uint64_t result = 0;
  for (uint32_t i=0 ; i< vec_length; i=i+1) {
    uint32_t offset= i*sizeof(uint64_t) + *budget;
    result =  ((uint64_t)buf[9 + offset] | (uint64_t)buf[10 + offset] << 8 | (uint64_t)buf[11 + offset] << 16 | (uint64_t)buf[12 + offset] << 24 | (uint64_t)buf[13 + offset] <<32 | (uint64_t)buf[14 + offset] << 40 | (uint64_t)buf[15 + offset] << 48 | (uint64_t)buf[16 + offset] << 56);
    uint64_t *ptr = (uint64_t *)malloc(sizeof(uint64_t));
    ptr[0]=result;
    vector_add(&v,ptr);
  }
  free(buf);
  return v;
}

void ic_writes_vec_nat64(vector v){
  write_magic();
  write_byte(0x01);
  write_byte(IDL_TYPE_VEC);
  write_byte(IDL_TYPE_NAT64);
  write_byte(0x01);
  write_byte(0x00);
  write_uleb128(vector_total(&v));
  int i =0;
  for (i = 0; i < vector_total(&v); i++)
    {
      uint64_t *val = vector_get(&v, i);
      write_nat64(val[0]);
    }
  ic0_msg_reply();
}

// int32
vector ic_reads_vec_int32(vector v){
  vector_init(&v);
  size_t len = (size_t)(ic0_msg_arg_data_size());
  uint8_t *buf = (uint8_t *)(malloc(len));
  ic0_msg_arg_data_copy((uint32_t)(buf), 0, (uint32_t)(len));
  match_magic(buf, len);
  match_byte(buf, len, 4, 0x01);
  match_byte(buf, len, 5, IDL_TYPE_VEC);
  match_byte(buf, len, 6, IDL_TYPE_INT32);
  match_byte(buf, len, 7, 0x01);
  match_byte(buf, len, 8, 0x00);
  uint8_t budget_var=1;
  uint8_t *budget;
  budget = &budget_var;
  uint32_t vec_length= read_uleb128(buf,9,budget);
  int32_t result = 0;
  for (uint32_t i=0 ; i< vec_length; i=i+1) {
    uint32_t offset= i*sizeof(int32_t ) + *budget;
    result =  ((int32_t)buf[9 + offset] | (int32_t)buf[10 + offset] << 8 | (int32_t)buf[11 + offset] << 16 | (int32_t)buf[12 + offset] << 24 );
    int32_t *ptr = (int32_t *)malloc(sizeof(int32_t));
    ptr[0]=result;
    vector_add(&v,ptr);
  }
  free(buf);
  return v;
}

void ic_writes_vec_int32(vector v){
  write_magic();
  write_byte(0x01);
  write_byte(IDL_TYPE_VEC);
  write_byte(IDL_TYPE_INT32);
  write_byte(0x01);
  write_byte(0x00);
  write_uleb128(vector_total(&v));
  int i =0;
  for (i = 0; i < vector_total(&v); i++)
    {
      int32_t *val = vector_get(&v, i);
      write_int32(val[0]);
    }
  ic0_msg_reply();
}

// nat32
vector ic_reads_vec_nat32(vector v){
  vector_init(&v);
  size_t len = (size_t)(ic0_msg_arg_data_size());
  uint8_t *buf = (uint8_t *)(malloc(len));
  ic0_msg_arg_data_copy((uint32_t)(buf), 0, (uint32_t)(len));
  match_magic(buf, len);
  match_byte(buf, len, 4, 0x01);
  match_byte(buf, len, 5, IDL_TYPE_VEC);
  match_byte(buf, len, 6, IDL_TYPE_NAT32);
  match_byte(buf, len, 7, 0x01);
  match_byte(buf, len, 8, 0x00);
  uint8_t budget_var=1;
  uint8_t *budget;
  budget = &budget_var;
  uint32_t vec_length= read_uleb128(buf,9,budget);
  uint32_t result = 0;
  for (uint32_t i=0 ; i< vec_length; i=i+1) {
    uint32_t offset= i*sizeof(uint32_t) + *budget;
    result =  ((uint32_t)buf[9 + offset] | (uint32_t)buf[10 + offset] << 8 | (uint32_t)buf[11 + offset] << 16 | (uint32_t)buf[12 + offset] << 24 );
    uint32_t *ptr = (uint32_t *)malloc(sizeof(uint32_t));
    ptr[0]=result;
    vector_add(&v,ptr);
  }
  free(buf);
  return v;
}

void ic_writes_vec_nat32(vector v){
  write_magic();
  write_byte(0x01);
  write_byte(IDL_TYPE_VEC);
  write_byte(IDL_TYPE_NAT32);
  write_byte(0x01);
  write_byte(0x00);
  write_uleb128(vector_total(&v));
  int i =0;
  for (i = 0; i < vector_total(&v); i++)
    {
      uint32_t *val = vector_get(&v, i);
      write_nat32(val[0]);
    }
  ic0_msg_reply();
}

// int16
vector ic_reads_vec_int16(vector v){
  vector_init(&v);
  size_t len = (size_t)(ic0_msg_arg_data_size());
  uint8_t *buf = (uint8_t *)(malloc(len));
  ic0_msg_arg_data_copy((uint32_t)(buf), 0, (uint32_t)(len));
  match_magic(buf, len);
  match_byte(buf, len, 4, 0x01);
  match_byte(buf, len, 5, IDL_TYPE_VEC);
  match_byte(buf, len, 6, IDL_TYPE_INT16);
  match_byte(buf, len, 7, 0x01);
  match_byte(buf, len, 8, 0x00);
  uint8_t budget_var=1;
  uint8_t *budget;
  budget = &budget_var;
  uint32_t vec_length= read_uleb128(buf,9,budget);
  int16_t result = 0;
  for (uint32_t i=0 ; i< vec_length; i=i+1) {
    uint32_t offset= i*sizeof(int16_t) + *budget;
    result =  ((int16_t)buf[9 + offset] | (int16_t)buf[10 + offset] << 8);
    int16_t *ptr = (int16_t *)malloc(sizeof(int16_t));
    ptr[0]=result;
    vector_add(&v,ptr);
  }
  free(buf);
  return v;
}

void ic_writes_vec_int16(vector v){
  write_magic();
  write_byte(0x01);
  write_byte(IDL_TYPE_VEC);
  write_byte(IDL_TYPE_INT16);
  write_byte(0x01);
  write_byte(0x00);
  write_uleb128(vector_total(&v));
  int i =0;
  for (i = 0; i < vector_total(&v); i++)
    {
      int16_t *val = vector_get(&v, i);
      write_int16(val[0]);
    }
  ic0_msg_reply();
}


// nat16
vector ic_reads_vec_nat16(vector v){
  vector_init(&v);
  size_t len = (size_t)(ic0_msg_arg_data_size());
  uint8_t *buf = (uint8_t *)(malloc(len));
  ic0_msg_arg_data_copy((uint32_t)(buf), 0, (uint32_t)(len));
  match_magic(buf, len);
  match_byte(buf, len, 4, 0x01);
  match_byte(buf, len, 5, IDL_TYPE_VEC);
  match_byte(buf, len, 6, IDL_TYPE_NAT16);
  match_byte(buf, len, 7, 0x01);
  match_byte(buf, len, 8, 0x00);
  uint8_t budget_var=1;
  uint8_t *budget;
  budget = &budget_var;
  uint32_t vec_length= read_uleb128(buf,9,budget);
  uint16_t result = 0;
  for (uint32_t i=0 ; i< vec_length; i=i+1) {
    uint32_t offset= i*sizeof(uint16_t) + *budget;
    result =  ((uint16_t)buf[9 + offset] | (uint16_t)buf[10 + offset] << 8 );
    uint16_t *ptr = (uint16_t *)malloc(sizeof(uint16_t));
    ptr[0]=result;
    vector_add(&v,ptr);
  }
  free(buf);
  return v;
}

void ic_writes_vec_nat16(vector v){
  write_magic();
  write_byte(0x01);
  write_byte(IDL_TYPE_VEC);
  write_byte(IDL_TYPE_NAT16);
  write_byte(0x01);
  write_byte(0x00);
  write_uleb128(vector_total(&v));
  int i =0;
  for (i = 0; i < vector_total(&v); i++)
    {
      uint16_t *val = vector_get(&v, i);
      write_nat16(val[0]);
    }
  ic0_msg_reply();
}



// int8
vector ic_reads_vec_int8(vector v){
  vector_init(&v);
  size_t len = (size_t)(ic0_msg_arg_data_size());
  uint8_t *buf = (uint8_t *)(malloc(len));
  ic0_msg_arg_data_copy((uint32_t)(buf), 0, (uint32_t)(len));
  match_magic(buf, len);
  match_byte(buf, len, 4, 0x01);
  match_byte(buf, len, 5, IDL_TYPE_VEC);
  match_byte(buf, len, 6, IDL_TYPE_INT8);
  match_byte(buf, len, 7, 0x01);
  match_byte(buf, len, 8, 0x00);
  uint8_t budget_var=1;
  uint8_t *budget;
  budget = &budget_var;
  uint32_t vec_length= read_uleb128(buf,9,budget);
  int8_t result = 0;
  for (uint32_t i=0 ; i< vec_length; i=i+1) {
    uint32_t offset= i*sizeof(int8_t) + *budget;
    result =  (int8_t)buf[9 + offset];
    int8_t *ptr = (int8_t *)malloc(sizeof(int8_t));
    ptr[0]=result;
    vector_add(&v,ptr);
  }
  free(buf);
  return v;
}

void ic_writes_vec_int8(vector v){
  write_magic();
  write_byte(0x01);
  write_byte(IDL_TYPE_VEC);
  write_byte(IDL_TYPE_INT8);
  write_byte(0x01);
  write_byte(0x00);
  write_uleb128(vector_total(&v));
  int i =0;
  for (i = 0; i < vector_total(&v); i++)
    {
      int8_t *val = vector_get(&v, i);
      write_byte(val[0]);
    }
  ic0_msg_reply();
}


// nat8
vector ic_reads_vec_nat8(vector v){
  vector_init(&v);
  size_t len = (size_t)(ic0_msg_arg_data_size());
  uint8_t *buf = (uint8_t *)(malloc(len));
  ic0_msg_arg_data_copy((uint32_t)(buf), 0, (uint32_t)(len));
  match_magic(buf, len);
  match_byte(buf, len, 4, 0x01);
  match_byte(buf, len, 5, IDL_TYPE_VEC);
  match_byte(buf, len, 6, IDL_TYPE_NAT8);
  match_byte(buf, len, 7, 0x01);
  match_byte(buf, len, 8, 0x00);
  uint8_t budget_var=1;
  uint8_t *budget;
  budget = &budget_var;
  uint32_t vec_length= read_uleb128(buf,9,budget);
  uint8_t result = 0;
  for (uint32_t i=0 ; i< vec_length; i=i+1) {
    uint32_t offset= i*sizeof(uint8_t) + *budget;
    result =  (uint8_t)buf[9 + offset];
    uint8_t *ptr = (uint8_t *)malloc(sizeof(uint8_t));
    ptr[0]=result;
    vector_add(&v,ptr);
  }
  free(buf);
  return v;
}

void ic_writes_vec_nat8(vector v){
  write_magic();
  write_byte(0x01);
  write_byte(IDL_TYPE_VEC);
  write_byte(IDL_TYPE_NAT8);
  write_byte(0x01);
  write_byte(0x00);
  write_uleb128(vector_total(&v));
  int i =0;
  for (i = 0; i < vector_total(&v); i++)
    {
      uint8_t *val = vector_get(&v, i);
      write_byte(val[0]);
    }
  ic0_msg_reply();
}
