#pragma once

typedef unsigned long crc32_t;

void crc32_init(crc32_t* crc);
void crc32_process_buffer(crc32_t* crc, const void* buf, int len);
void crc32_final(crc32_t* crc);
crc32_t crc32_get_table_entry(unsigned int slot);

inline crc32_t crc32_process_single_buffer(const void* buf, int len) {
	crc32_t crc;

	crc32_init(&crc);
	crc32_process_buffer(&crc, buf, len);
	crc32_final(&crc);

	return crc;
}