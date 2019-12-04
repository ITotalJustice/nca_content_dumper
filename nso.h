#ifndef _NSO_H_
#define _NSO_H_

#include <stdint.h>

#define NSO_MAGIC 0x304F534E


typedef struct 
{
    uint32_t file_offset;
    uint32_t memory_offset;
    uint32_t decompressed_size;
} segment_header_t;

typedef struct
{
    uint32_t region_rodata_offset;
    uint32_t region_size;
} rodata_relative_extent_t;

typedef struct
{
    uint8_t sha256[0x20];
} segment_hash_t;

typedef struct
{
    uint32_t magic;
    uint32_t version;
    uint8_t _0x8[0x4]; // empty.
    segment_header_t text;
    uint32_t module_offset;
    segment_header_t rodata;
    uint32_t module_file_size;
    segment_header_t data;
    uint32_t bss_size;
    uint8_t value_of_build_id[0x20];
    uint32_t text_compressed_size;
    uint32_t rodata_compressed_size;
    uint32_t data_compressed_size;
    uint8_t _0x6C[0x1C]; // empty.
    rodata_relative_extent_t api_info;
    rodata_relative_extent_t dynstr;
    rodata_relative_extent_t dynsym;
    segment_hash_t hashes[0x3];
} nso_header_t;

#endif