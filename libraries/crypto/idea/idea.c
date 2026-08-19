/**
 * @file    idea.c
 * @brief   Provides Implementation for International Data Encryption Algorithm (IDEA).
 * @version 0.1
 * @date    2026-08-08
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "idea.h"
#include <stddef.h>

typedef struct
{
    uint16_t textBlock[4];
    uint16_t encryptBlock[4];
    uint16_t iv[4];
    uint16_t encryptPartialKey[52];
    uint16_t decryptPartialKey[52];
} idea_block_directory_t;

idea_block_directory_t idea_block = {0};
uint32_t cipher_text_len; // cipher text length - returned after encryption

static void idea_round(uint16_t *y_out, uint16_t *x_in, uint16_t *z_in);
static void idea_trafo(uint16_t *y_out, uint16_t *x_in, uint16_t *z_in);
static void idea_gen_partial_keys(IDEA_CONFIG_t *config);
static void idea_encrypt_block();

static uint16_t idea_mulop(uint16_t i_1, uint16_t i_2);
static inline uint16_t idea_addop(uint16_t a_1, uint16_t a_2);
static inline uint16_t idea_xorop(uint16_t x_1, uint16_t x_2);

/*************************************************************/

/**
 * @brief API to initialize IDEA.
 * 
 * @param config         Pointer to IDEA configurations. Use IDEA_CONFIG_t structure to set the required configurations.
 * @return IDEA_STATUS_t Status of the operation. Refer to enum IDEA_STATUS_t.
 */
IDEA_STATUS_t IDEA_Initialize(IDEA_CONFIG_t *config)
{
    if (config == NULL)
        return IDEA_STATUS_INVALID_PARAMETER;

    if (config->keyLen != 16) // The key must be 128 bits
        return IDEA_STATUS_INVALID_KEY_LENGTH;

    if (config->IV_type == IDEA_IV_RANDOM)
    {
        for (uint8_t i = 0; i < 4; i++)
            idea_block.iv[i] = i + 10;  // TODO: This has to be randomly generated.
    }
    else if (config->IV_type == IDEA_IV_USER_DEFINED)
    {
        for (uint8_t i = 0; i < 4; i++)
            idea_block.iv[i] = (config->IV[2*i] << 8) | config->IV[2*i+1];
    }
    else
    {
        for (uint8_t i = 0; i < 4; i++)
            idea_block.iv[i] = 0;       // Set IV = 0.
    }

    cipher_text_len = 0;

    idea_gen_partial_keys(config);

    return IDEA_STATUS_SUCCESS;
}

/**
 * @brief API to encrypt message using IDEA.
 * 
 * @param config         Pointer to IDEA configurations. Use IDEA_CONFIG_t structure to set the required configurations.
 * @return IDEA_STATUS_t Status of the operation. Refer to enum IDEA_STATUS_t.
 */
IDEA_STATUS_t IDEA_EncryptText(IDEA_CONFIG_t *config)
{
    if (config == NULL)
        return IDEA_STATUS_INVALID_PARAMETER;

    if (config->keyLen != 16) // The key must be 128 bits
        return IDEA_STATUS_INVALID_KEY_LENGTH;

    uint8_t *pt = config->plainText;
    uint8_t *ct = config->cipherText;

    uint32_t len = config->plainTextLen;

    if (len == 0)
        return IDEA_STATUS_INVALID_MESSAGE_LENGTH;

    uint8_t padding = 8 - (len % 8);

    if (padding == 0)
        padding = 8; // Add another padding at the end if the plain text is already aligned

    uint8_t block[8];

    for (uint32_t offset = 0; offset < len + padding; offset += 8)
    {
        // Construct an 8-byte plaintext block
        for (uint8_t j = 0; j < 8; j++)
        {
            if ((offset+j) < len)
                block[j] = pt[offset+j];
            else
                block[j] = padding;
        }

        idea_block.textBlock[0] = (block[0] << 8) | block[1];
        idea_block.textBlock[1] = (block[2] << 8) | block[3];
        idea_block.textBlock[2] = (block[4] << 8) | block[5];
        idea_block.textBlock[3] = (block[6] << 8) | block[7];

        // CBC xor
        if (offset == 0)
        {
            idea_block.textBlock[0] ^= idea_block.iv[0];
            idea_block.textBlock[1] ^= idea_block.iv[1];
            idea_block.textBlock[2] ^= idea_block.iv[2];
            idea_block.textBlock[3] ^= idea_block.iv[3];
        }
        else
        {
            idea_block.textBlock[0] ^= idea_block.encryptBlock[0];
            idea_block.textBlock[1] ^= idea_block.encryptBlock[1];
            idea_block.textBlock[2] ^= idea_block.encryptBlock[2];
            idea_block.textBlock[3] ^= idea_block.encryptBlock[3];
        }

        // Encrypt
        idea_encrypt_block();

        // Store ciphertext
        ct[offset + 0] = (uint8_t)(idea_block.encryptBlock[0] >> 8);
        ct[offset + 1] = (uint8_t)(idea_block.encryptBlock[0]);

        ct[offset + 2] = (uint8_t)(idea_block.encryptBlock[1] >> 8);
        ct[offset + 3] = (uint8_t)(idea_block.encryptBlock[1]);

        ct[offset + 4] = (uint8_t)(idea_block.encryptBlock[2] >> 8);
        ct[offset + 5] = (uint8_t)(idea_block.encryptBlock[2]);

        ct[offset + 6] = (uint8_t)(idea_block.encryptBlock[3] >> 8);
        ct[offset + 7] = (uint8_t)(idea_block.encryptBlock[3]);

        cipher_text_len += 8;
    }

    return IDEA_STATUS_SUCCESS;
}

/**
 * @brief API to get the actual length of the cipher text in bytes.
 * 
 * @param config    Pointer to IDEA configurations. Use IDEA_CONFIG_t structure to set the required configurations.
 * @return uint32_t Number of bytes.
 */
uint32_t IDEA_GetCipherTextLength(IDEA_CONFIG_t *config)
{
    if (config != NULL)
        return cipher_text_len;
    return 0;
}

/**
 * @brief API to get the value of the Initialization Vector uint16_t [4].
 * 
 * @param config         Pointer to IDEA configurations. Use IDEA_CONFIG_t structure to set the required configurations.
 * @param dest           Location to store the IV.
 * @return IDEA_STATUS_t Status of the operation. Refer to enum IDEA_STATUS_t.
 */
IDEA_STATUS_t IDEA_GetIV(IDEA_CONFIG_t *config, uint16_t *dest)
{
    if (config == NULL)
        return IDEA_STATUS_INVALID_PARAMETER;

    uint8_t i = 0;
    while(i < 4)
    {
        *dest++ = idea_block.iv[i];
        ++i;
    }

    return IDEA_STATUS_SUCCESS;
}

/*************************************************************/

/* IDEA operation functions */

static void idea_encrypt_block()
{
    uint16_t *y = idea_block.encryptBlock;
    uint16_t *x = idea_block.textBlock;
    uint16_t *z = idea_block.encryptPartialKey;

    // Rounds
    for (uint16_t i = 0; i < 8; i++)
    {
        if (i == 0)
        {
            idea_round(y, x, z);
        }
        else
        {
            idea_round(y, y, z);
        }
        z +=6;
    }

    // Output transformation
    idea_trafo(y, y, z);
}

static void idea_round(uint16_t *y_out, uint16_t *x_in, uint16_t *z_in)
{
    uint16_t X1 = x_in[0];
    uint16_t X2 = x_in[1];
    uint16_t X3 = x_in[2];
    uint16_t X4 = x_in[3];

    uint16_t Z1 = z_in[0];
    uint16_t Z2 = z_in[1];
    uint16_t Z3 = z_in[2];
    uint16_t Z4 = z_in[3];
    uint16_t Z5 = z_in[4];
    uint16_t Z6 = z_in[5];

    // Round state - S1, S2, S3, and S4
    uint16_t S1 = idea_mulop(X1, Z1);   // S1 = X1 * Z1
    uint16_t S2 = idea_addop(X2, Z2);   // S2 = X2 + Z2
    uint16_t S3 = idea_addop(X3, Z3);   // S3 = X3 + Z3
    uint16_t S4 = idea_mulop(X4, Z4);   // S4 = X4 * Z4

    // Round state - S5 and S6
    uint16_t S5 = idea_xorop(S1, S3);
    uint16_t S6 = idea_xorop(S2, S4);

    // Round state - S7 and S8
    uint16_t S7 = idea_mulop(Z5, S5);
    uint16_t S8 = idea_addop(S6, S7);

    // Round state - S9 and S10
    uint16_t S9  = idea_mulop(Z6, S8);
    uint16_t S10 = idea_addop(S7, S9);

    // Round state - S11, S12, S13, and S14
    uint16_t S11 = idea_xorop(S1, S9);
    uint16_t S12 = idea_xorop(S3, S9);
    uint16_t S13 = idea_xorop(S2, S10);
    uint16_t S14 = idea_xorop(S4, S10);

    // Round output
    y_out[0] = S11;
    y_out[1] = S12;
    y_out[2] = S13;
    y_out[3] = S14;
}

static void idea_trafo(uint16_t *y_out, uint16_t *x_in, uint16_t *z_in)
{
    uint16_t X1 = x_in[0];
    uint16_t X2 = x_in[1];
    uint16_t X3 = x_in[2];
    uint16_t X4 = x_in[3];

    uint16_t Z1 = z_in[0];
    uint16_t Z2 = z_in[1];
    uint16_t Z3 = z_in[2];
    uint16_t Z4 = z_in[3];

    // Output transformation
    y_out[0] = idea_mulop(X1, Z1);
    y_out[1] = idea_addop(X3, Z2);
    y_out[2] = idea_addop(X2, Z3);
    y_out[3] = idea_mulop(X4, Z4);
}

static void idea_gen_partial_keys(IDEA_CONFIG_t *config)
{
    uint8_t *k = config->key;
    uint16_t *ek = idea_block.encryptPartialKey;

    // All keys are stored in big-endian order
    // Copy the key into the partial key buffer in 16 bit format
    for (uint8_t i = 0; i < 8; i++)
    {
        ek[i] = (k[2*i] << 8) | k[2*i+1];
    }

    // Next 44 partial keys are derived from ek by left rotating by
    // 25 bits.
    for (uint8_t i = 8; i < 52; i++)
    {
        if((i % 8) == 6)
           ek[i] = (uint16_t)((ek[i-7] << 9) | (ek[i-14] >> 7));
        else if((i % 8) == 7)
           ek[i] = (uint16_t)((ek[i-15] << 9) | (ek[i-14] >> 7));
        else
           ek[i] = (uint16_t)((ek[i-7] << 9) | (ek[i-6] >> 7));
    }
}

/*************************************************************/

/* Internal operations */

#ifdef IDEA_FAST_MULOP
    static uint16_t idea_mulop(uint16_t i_1, uint16_t i_2)
    {
        uint32_t p = (uint32_t)i_1 * i_2;

        if (p != 0) {
            uint16_t low = p & 0xFFFF;
            uint16_t high = p >> 16;
            return (low >= high) ? (low - high) : (low - high + 1);
        } else {
            return (1 - i_1 - i_2);
        }
    }
#else // Use regular mudulo-multiplier operation
    static uint16_t idea_mulop(uint16_t i_1, uint16_t i_2)
    {
        uint32_t a = 0, b = 0;
        uint32_t res = 0;

        if (i_1 == 0)
            a = 65536;
        else
            a = (uint32_t)i_1;

        if (i_2 == 0)
            b = 65536;
        else
            b = (uint32_t)i_2;

        res = (a * b) % 65537;

        if (res == 65536) {
            return 0;
        }

        return (uint16_t)res;
    }
#endif /* IDEA_FAST_MULOP */

static inline uint16_t idea_addop(uint16_t a_1, uint16_t a_2)
{
    uint32_t res = (uint32_t)(a_1 + a_2) & 0xffff;
    return (uint16_t)res;
}

static inline uint16_t idea_xorop(uint16_t x_1, uint16_t x_2)
{
    uint16_t res = x_1 ^ x_2;
    return (uint16_t)res;
}
