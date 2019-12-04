#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "nca.h"


bool nca_check_if_magic_valid(uint32_t magic)
{
    switch (magic)
    {
        case NCA0_MAGIC: return true;
        case NCA2_MAGIC: return true;
        case NCA3_MAGIC: return true;
        default:
        {
            printf("incorrect nca magic. got %u\n", magic);
            return false;
        }
    }
}

void nca_get_header(nca_struct_t *ptr, uint64_t offset)
{
    fseek(ptr->f, 0, SEEK_SET);
    fread(&ptr->header, NCA_HEADER_SIZE, 1, ptr->f);
}

void nca_get_section_header(nca_struct_t *ptr, uint64_t offset)
{
    fseek(ptr->f, offset, SEEK_SET);
    fread(ptr->section_header, (NCA_SECTION_HEADER_SIZE * 4), 1, ptr->f);
}

void nca_get_actual_section_offsets_sizes(nca_struct_t *ptr)
{
    for (uint8_t i = 0; i < 4; i++)
    {
        if (!ptr->section_header[i].version)
            break; // we've now got the total of sections.

        ptr->section_info[i].offset = (ptr->header.section_table[i].media_start_offset * 0x200) + ptr->section_header[i].pfs0_sb.pfs0_offset;
        ptr->section_info[i].size = (ptr->header.section_table[i].media_end_offset * 0x200) - ptr->section_info[i].offset;
        ptr->section_total = i + 1;
    }
}

void nca_dump_header(nca_struct_t *ptr)
{
    FILE *f = fopen("out_nca_header", "wb");
    if (!f)
    {
        printf("failed to create file for dumping\n");
        return;
    }

    fwrite(&ptr->header, NCA_HEADER_SIZE, 1, f);
    fclose(f);
}

void nca_dump_section_header(nca_struct_t *ptr)
{
    FILE *f = fopen("out_nca_section_header", "wb");
    if (!f)
    {
        printf("failed to create file for dumping\n");
        return;
    }

    fwrite(&ptr->section_header, NCA_SECTION_HEADER_SIZE, 1, f);
    fclose(f);
}