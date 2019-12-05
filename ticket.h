#ifndef _TICKET_H_
#define _TICKET_H_

#include <stdint.h>


#define RSA_4096_SHA1_SIZE      0x200
#define RSA_2048_SHA1_SIEZ      0x100
#define ECDSA_SHA1_SIZE         0x3C
#define RSA_4096_SHA256_SIZE    0x200
#define RSA_2048_SHA256_SIZE    0x100
#define ECDSA_SHA256_SIZE       0x3C

#define RSA_4096_SHA1_PADDING       0x3C
#define RSA_2048_SHA1_SIEZ          0x3C
#define ECDSA_SHA1_PADDING          0x40
#define RSA_4096_SHA256_PADDING     0x3C
#define RSA_2048_SHA256_PADDING     0x3C
#define ECDSA_SHA256_PADDING        0x40

typedef enum
{
    TicketType_Common       = 0x0,
    TicketType_Personalised = 0x1
} TicketType;

typedef enum
{
    SignatureType_RSA_4096_SHA1     = 0x010000,
    SignatureType_RSA_2048_SHA1     = 0x010001,
    SignatureType_ECDSA_SHA1        = 0x010002,
    SignatureType_RSA_4096_SHA256   = 0x010003,
    SignatureType_RSA_2048_SHA256   = 0x010004,
    SignatureType_ECDSA_SHA256      = 0x010005
} SignatureType;

typedef struct
{
    uint32_t type;  // see SignatureType.
    uint8_t *signature; // signature data + padding.
} signature_data_t;

typedef struct
{
    uint8_t issuer[0x40];
    uint8_t title_key_block[0x100];
    uint8_t _0x140;                  //unkown.
    uint8_t title_key_type;          // see TicketType.
    uint8_t _0x142[0x3];             //unkown.
    uint8_t master_key_revision;
    uint8_t _0x146[0xA];             //unkown.
    uint64_t ticket_id;
    uint64_t device_id;
    uint8_t rights_id[0x10];
    uint32_t account_id;
    uint8_t _0x174[0xC];             //unkown.
    uint8_t title_key_enc[0x10];
    uint8_t _0x190[0x130];           //unkown.
} ticket_data_t;

#endif