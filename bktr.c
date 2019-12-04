#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#include "bktr.h"


bool bktr_check_if_magic_valid(uint32_t magic)
{
    if (magic != BKTR_MAGIC)
    {
        printf("\ngot wrong magic %u\n", magic);
        return false;
    }
    return true;
}