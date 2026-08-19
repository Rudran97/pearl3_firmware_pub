/**
 * @file    idea.h
 * @brief   Provides APIs for International Data Encryption Algorithm (IDEA).
 * @version 0.1
 * @date    2026-08-08
 *
 * @copyright Copyright (c) 2026
 *
 */

#ifndef _IDEA_H_
#define _IDEA_H_

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

/* Use Low-High Algorith to compute the modulo-multiplication */
// #define IDEA_FAST_MULOP

/* Generate predefined test vectors for IDEA */
// #define IDEA_TEST_VECTOR

/* Defines encrypt/decrypt status */
typedef enum
{
    IDEA_STATUS_SUCCESS = 0,
    IDEA_STATUS_FAIL,
    IDEA_STATUS_INVALID_KEY_LENGTH,
    IDEA_STATUS_INVALID_PARAMETER,
    IDEA_STATUS_INVALID_MESSAGE_LENGTH
} IDEA_STATUS_t;

/* Defines IV type */
typedef enum
{
    IDEA_IV_ZERO = 0,
    IDEA_IV_RANDOM,
    IDEA_IV_USER_DEFINED
} IDEA_IV_t;

/*************************************************************/

/* Structure defining the configurations of IDEA */
typedef struct
{
    uint8_t *key;
    uint8_t keyLen;
    uint8_t *plainText;
    uint32_t plainTextLen;
    uint8_t *cipherText;
    IDEA_IV_t IV_type;
    uint8_t *IV;
} IDEA_CONFIG_t;

/*************************************************************/

/**
 * @brief API to initialize IDEA.
 * 
 * @param config         Pointer to IDEA configurations. Use IDEA_CONFIG_t structure to set the required configurations.
 * @return IDEA_STATUS_t Status of the operation. Refer to enum IDEA_STATUS_t.
 */
IDEA_STATUS_t IDEA_Initialize(IDEA_CONFIG_t *config);

/**
 * @brief API to encrypt message using IDEA.
 * 
 * @param config         Pointer to IDEA configurations. Use IDEA_CONFIG_t structure to set the required configurations.
 * @return IDEA_STATUS_t Status of the operation. Refer to enum IDEA_STATUS_t.
 */
IDEA_STATUS_t IDEA_EncryptText(IDEA_CONFIG_t *config);

/**
 * @brief API to get the actual length of the cipher text in bytes.
 * 
 * @param config    Pointer to IDEA configurations. Use IDEA_CONFIG_t structure to set the required configurations.
 * @return uint32_t Number of bytes.
 */
uint32_t IDEA_GetCipherTextLength(IDEA_CONFIG_t *config);

/**
 * @brief API to get the value of the Initialization Vector uint16_t [4].
 * 
 * @param config         Pointer to IDEA configurations. Use IDEA_CONFIG_t structure to set the required configurations.
 * @param dest           Location to store the IV.
 * @return IDEA_STATUS_t Status of the operation. Refer to enum IDEA_STATUS_t.
 */
IDEA_STATUS_t IDEA_GetIV(IDEA_CONFIG_t *config, uint16_t *dest);

/*************************************************************/

/* Structure defining the example test vectors for IDEA
 * https://sources.debian.org/src/thunderbird/1%3A140.12.0esr-1~deb12u1/comm/third_party/libgcrypt/cipher/idea.c?utm_source=chatgpt.com */

#ifdef IDEA_TEST_VECTOR
    static struct {
        uint8_t key[16];
        uint8_t plain[8];
        uint8_t cipher[8];
    } idea_test_vectors[] = {
        { { 0x00, 0x01, 0x00, 0x02, 0x00, 0x03, 0x00, 0x04,      // key
            0x00, 0x05, 0x00, 0x06, 0x00, 0x07, 0x00, 0x08 },
          { 0x00, 0x00, 0x00, 0x01, 0x00, 0x02, 0x00, 0x03 },    // plain
          { 0x11, 0xFB, 0xED, 0x2B, 0x01, 0x98, 0x6D, 0xE5 } },  // cipher

        { { 0x00, 0x01, 0x00, 0x02, 0x00, 0x03, 0x00, 0x04,      // key
            0x00, 0x05, 0x00, 0x06, 0x00, 0x07, 0x00, 0x08 },
          { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 },    // plain
          { 0x54, 0x0E, 0x5F, 0xEA, 0x18, 0xC2, 0xF8, 0xB1 } },  // cipher

        { { 0x00, 0x01, 0x00, 0x02, 0x00, 0x03, 0x00, 0x04,      // key
            0x00, 0x05, 0x00, 0x06, 0x00, 0x07, 0x00, 0x08 },
          { 0x00, 0x19, 0x32, 0x4B, 0x64, 0x7D, 0x96, 0xAF },    // plain
          { 0x9F, 0x0A, 0x0A, 0xB6, 0xE1, 0x0C, 0xED, 0x78 } },  // cipher

        { { 0x00, 0x01, 0x00, 0x02, 0x00, 0x03, 0x00, 0x04,      // key
            0x00, 0x05, 0x00, 0x06, 0x00, 0x07, 0x00, 0x08 },
          { 0xF5, 0x20, 0x2D, 0x5B, 0x9C, 0x67, 0x1B, 0x08 },    // plain
          { 0xCF, 0x18, 0xFD, 0x73, 0x55, 0xE2, 0xC5, 0xC5 } },  // cipher

        { { 0x00, 0x01, 0x00, 0x02, 0x00, 0x03, 0x00, 0x04,      // key
            0x00, 0x05, 0x00, 0x06, 0x00, 0x07, 0x00, 0x08 },
          { 0xFA, 0xE6, 0xD2, 0xBE, 0xAA, 0x96, 0x82, 0x6E },    // plain
          { 0x85, 0xDF, 0x52, 0x00, 0x56, 0x08, 0x19, 0x3D } },  // cipher

        { { 0x00, 0x01, 0x00, 0x02, 0x00, 0x03, 0x00, 0x04,      // key
            0x00, 0x05, 0x00, 0x06, 0x00, 0x07, 0x00, 0x08 },
          { 0x0A, 0x14, 0x1E, 0x28, 0x32, 0x3C, 0x46, 0x50 },    // plain
          { 0x2F, 0x7D, 0xE7, 0x50, 0x21, 0x2F, 0xB7, 0x34 } },  // cipher

        { { 0x00, 0x01, 0x00, 0x02, 0x00, 0x03, 0x00, 0x04,      // key
            0x00, 0x05, 0x00, 0x06, 0x00, 0x07, 0x00, 0x08 },
          { 0x05, 0x0A, 0x0F, 0x14, 0x19, 0x1E, 0x23, 0x28 },    // plain
          { 0x7B, 0x73, 0x14, 0x92, 0x5D, 0xE5, 0x9C, 0x09 } },  // cipher

        { { 0x00, 0x05, 0x00, 0x0A, 0x00, 0x0F, 0x00, 0x14,      // key
            0x00, 0x19, 0x00, 0x1E, 0x00, 0x23, 0x00, 0x28 },
          { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 },    // plain
          { 0x3E, 0xC0, 0x47, 0x80, 0xBE, 0xFF, 0x6E, 0x20 } },  // cipher

        { { 0x3A, 0x98, 0x4E, 0x20, 0x00, 0x19, 0x5D, 0xB3,      // key
            0x2E, 0xE5, 0x01, 0xC8, 0xC4, 0x7C, 0xEA, 0x60 },
          { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 },    // plain
          { 0x97, 0xBC, 0xD8, 0x20, 0x07, 0x80, 0xDA, 0x86 } },  // cipher

        { { 0x00, 0x64, 0x00, 0xC8, 0x01, 0x2C, 0x01, 0x90,      // key
            0x01, 0xF4, 0x02, 0x58, 0x02, 0xBC, 0x03, 0x20 },
          { 0x05, 0x32, 0x0A, 0x64, 0x14, 0xC8, 0x19, 0xFA },    // plain
          { 0x65, 0xBE, 0x87, 0xE7, 0xA2, 0x53, 0x8A, 0xED } },  // cipher

        { { 0x9D, 0x40, 0x75, 0xC1, 0x03, 0xBC, 0x32, 0x2A,      // key
            0xFB, 0x03, 0xE7, 0xBE, 0x6A, 0xB3, 0x00, 0x06 },
          { 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08 },    // plain
          { 0xF5, 0xDB, 0x1A, 0xC4, 0x5E, 0x5E, 0xF9, 0xF9 } }   // cipher
    };

    /**
     * @brief API to self test IDEA using predefined test vectors.
     * 
     */
    IDEA_STATUS_t idea_SelfTest()
    {
        for (uint32_t i = 0; i < sizeof(idea_test_vectors) / sizeof(idea_test_vectors[0]); i++)
        {
            uint8_t *test_key = idea_test_vectors[i].key;
            uint8_t key_len = sizeof(idea_test_vectors[i].key) / sizeof(idea_test_vectors[i].key[0]);
            uint8_t *test_pt = idea_test_vectors[i].plain;
            uint32_t pt_len = sizeof(idea_test_vectors[i].plain) / sizeof(idea_test_vectors[i].plain[0]);
            uint8_t *test_ct = idea_test_vectors[i].cipher;

            uint8_t ct[32] = {0};

            IDEA_CONFIG_t idea_self_test_config = {
                .key = test_key,
                .keyLen = key_len,
                .plainText = test_pt,
                .plainTextLen = pt_len,
                .cipherText = ct,
                .IV_type = IDEA_IV_ZERO
            };

            if (IDEA_Initialize(&idea_self_test_config) != IDEA_STATUS_SUCCESS)
                return IDEA_STATUS_FAIL;

            if (IDEA_EncryptText(&idea_self_test_config) != IDEA_STATUS_SUCCESS)
                return IDEA_STATUS_FAIL;

            uint32_t cipher_len = IDEA_GetCipherTextLength(&idea_self_test_config);
            if (cipher_len != 16)  // 8 extra bytes due to padding
                return IDEA_STATUS_FAIL;

            if (memcmp(ct, test_ct, 8))
                return IDEA_STATUS_FAIL;
        }

        return IDEA_STATUS_SUCCESS;
    }
#endif /* IDEA_TEST_VECTOR */

#endif /* _IDEA_H_ */
