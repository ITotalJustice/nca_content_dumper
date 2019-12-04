#include <stdio.h>

#include "nca.h"


int main(int argc, char *argv[])
{
    nca_struct_t ptr;

    if (argc != 2)
    {
        printf("not enough args\n");
        return 1;
    }
    
    // try and open the file.
    if (!(ptr.f = fopen(argv[1], "rb")))
    {
        printf("couldnt open file\n");
        return 1;
    }

    // get the header of the nca.
    nca_get_header(&ptr, 0);

    // check if the magic is valid (nca0, 2, 3).
    if (!nca_check_if_magic_valid(ptr.header.magic))
    {
        fclose(ptr.f);
        return 1;
    }

    // get the section headers (theres up to 4 of them).
    nca_get_section_header(&ptr, NCA_HEADER_SIZE);

    // get the actual offset and size for each section (pfs0 and romfs).
    nca_get_actual_section_offsets_sizes(&ptr);
    
    // lets parse and dump the data!
    for (uint8_t i = 0; i < ptr.section_total; i++)
    {
        switch (ptr.section_header[i].fs_type)
        {
            case NcaFileSystemType_PFS0:
            {
                pfs0_start(ptr.f, ptr.section_info[i].offset);
            }

            default:
            {
                continue; // only doing pfs0 for now, will do romfs later.
            }
        }
    }

    return 0;
}