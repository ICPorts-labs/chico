
extern uint8_t IDL_MAGIC[4];
extern uint8_t IDL_TYPE_int;
extern uint8_t IDL_TYPE_text;

void write_magic();

void write_byte(uint8_t byte);

void write_return_byte(int x);

void write_uleb128 (uint32_t x);

void ic_log_message(const char *message);

void match_byte(const uint8_t *buf, size_t len, int off, uint8_t byte);

void match_magic(const uint8_t *buf, size_t len);


void ic_writes_text(char *result);

void ic_writes_int8(int8_t  val);
