#ifndef _ROMFS_H_
#define _ROMFS_H_

#include <stdint.h>

#include "ivfc.h"


typedef struct
{
    uint8_t _0x0[0x8]; // seems to always be 02, 00, 00, 03, 03, 00, 00, 00.
    ivfc_header_t ivfc_header;
} romfs_superblock_t;

#endif