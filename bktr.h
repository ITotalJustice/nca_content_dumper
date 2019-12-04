#ifndef _BKTR_H_
#define _BKTR_H_

#include <stdint.h>
#include <stdbool.h>

#define BKTR_MAGIC 0x52544B42


typedef struct
{
    uint64_t offset;
    uint64_t size;
    uint32_t magic;
    uint8_t unsigned_32[0x4];
    uint8_t signed_32[0x4];
    uint8_t unkown[0x4];
} bktr_entry_t;

typedef struct
{
    bktr_entry_t entry_1;
    bktr_entry_t entry_2;
    uint8_t _0x40[0x4];
    uint8_t _0x44[0x4];
} bktr_header_t;


//
bool bktr_check_if_magic_valid(uint32_t magic);

#endif