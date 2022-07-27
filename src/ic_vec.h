#ifndef VECTOR_H
#define VECTOR_H

#define VECTOR_INIT_CAPACITY 4

#define VECTOR_INIT(vec) vector vec; vector_init(&vec)
#define VECTOR_ADD(vec, item) vector_add(&vec, (void *) item)
#define VECTOR_SET(vec, id, item) vector_set(&vec, id, (void *) item)
#define VECTOR_GET(vec, type, id) (type) vector_get(&vec, id)
#define VECTOR_DELETE(vec, id) vector_delete(&vec, id)
#define VECTOR_TOTAL(vec) vector_total(&vec)
#define VECTOR_FREE(vec) vector_free(&vec)

typedef struct vector {
    void **items;
    int capacity;
    int total;
} vector;

void vector_init(vector *);
int vector_total(vector *);
static void vector_resize(vector *, int);
void vector_add(vector *, void *);
void vector_set(vector *, int, void *);
void *vector_get(vector *, int);
void vector_delete(vector *, int);
void vector_free(vector *);

#endif

vector ic_reads_vec_int64();
void ic_writes_vec_int64(vector v);
vector ic_reads_vec_nat64();
void ic_writes_vec_nat64(vector v);

vector ic_reads_vec_int32();
void ic_writes_vec_int32(vector v);
vector ic_reads_vec_nat32();
void ic_writes_vec_nat32(vector v);

vector ic_reads_vec_int16();
void ic_writes_vec_int16(vector v);
vector ic_reads_vec_nat16();
void ic_writes_vec_nat16(vector v);

vector ic_reads_vec_int8();
void ic_writes_vec_int8(vector v);
vector ic_reads_vec_nat8();
void ic_writes_vec_nat8(vector v);

vector ic_reads_vec_text();
void ic_writes_vec_text(vector v);
