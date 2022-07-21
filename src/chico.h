
extern uint8_t IDL_MAGIC[4];
extern uint8_t IDL_TYPE_INT;
extern uint8_t IDL_TYPE_TEXT;
extern uint8_t IDL_TYPE_BOOL;
extern uint8_t IDL_TYPE_NAT8;
extern uint8_t IDL_TYPE_NAT16;
extern uint8_t IDL_TYPE_NAT32;
extern uint8_t IDL_TYPE_NAT64;
extern uint8_t IDL_TYPE_INT8;
extern uint8_t IDL_TYPE_INT16;
extern uint8_t IDL_TYPE_INT32;
extern uint8_t IDL_TYPE_INT64;
extern uint8_t IDL_TYPE_FLOAT32;
extern uint8_t IDL_TYPE_FLOAT64;
extern uint8_t IDL_TYPE_VEC;
extern uint8_t IDL_TYPE_RECORD;
extern uint8_t IDL_TYPE_PRINCIPAL;


void trap(const char *str);
  
void write_magic();

void write_byte(uint8_t byte);

void write_return_byte(int x);

void write_uleb128 (uint32_t x);

void ic_log_message(const char *message);

void match_byte(const uint8_t *buf, size_t len, int off, uint8_t byte);

void match_magic(const uint8_t *buf, size_t len);


char* ic_reads_text();
void ic_writes_text(char *result);

void write_int64(int64_t  val);
void write_nat64(uint64_t  val);
void write_int32(int32_t  val);
void write_nat32(uint32_t  val);
void write_int16(int16_t  val);
void write_nat16(uint16_t  val);
void write_int8(int8_t  val);
void write_nat8(uint8_t  val);



void ic_writes_int8(int8_t  val);
void ic_writes_int16(int16_t  val);
void ic_writes_int32(int32_t  val);
void ic_writes_int64(int64_t  val);

void ic_writes_nat8(uint8_t  val);
void ic_writes_nat16(uint16_t  val);
void ic_writes_nat32(uint32_t  val);
void ic_writes_nat64(uint64_t  val);

int8_t ic_reads_int8();
int16_t ic_reads_int16();
int32_t ic_reads_int32();
int64_t ic_reads_int64();

uint8_t ic_reads_nat8();
uint16_t ic_reads_nat16();
uint32_t ic_reads_nat32();
uint64_t ic_reads_nat64();

_Bool ic_reads_bool();
void ic_writes_bool(_Bool val);
