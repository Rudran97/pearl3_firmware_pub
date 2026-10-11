#include "prv_timer0.h"
#include "prv_gpio.h"
#include "prv_interrupt.h"
#include "prv_serial.h"

#define IDEA_TEST_VECTOR
#include "idea.h"

uint8_t text[] = {0x11, 0x11, 0x22, 0x22, 0x44, 0x44, 0x88, 0x88};
const char *message = "Hello World!!! Plain text for IDEA algorithm";

// uint8_t key[] = {0x00, 0x01, 0x00, 0x02, 0x00, 0x03, 0x00, 0x04, 0x00, 0x05, 0x00, 0x06, 0x00, 0x07, 0x00, 0x08};
uint8_t key[] = {0x5a, 0x14, 0xfb, 0x3e, 0x02, 0x1c, 0x79, 0xe0, 0x60, 0x81, 0x46, 0xa0, 0x11, 0x7b, 0xff, 0x03};
uint8_t iv[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};

uint8_t cipher[128] = {0};
uint8_t decipher[128] = {0};
uint16_t iv_used[4] = {0};

int main ()
{
    SysTick_Init(TIMERms_const);
    Serial_Initialize(115200);
    ENABLE_GLOBAL_INTERRUPT();

    IDEA_CONFIG_t idea_config = {
        .key = key,
        .keyLen = sizeof(key) / sizeof(key[0]),
        .plainText = (uint8_t *)message,
        .textLen = strlen(message),
        .cipherText = cipher,
        .decryptText = decipher,
        .IV_type = IDEA_IV_USER_DEFINED,
        .IV = iv
    };

    if (idea_SelfTest() != IDEA_STATUS_SUCCESS)
        while(1);

    if (IDEA_Initialize(&idea_config) != IDEA_STATUS_SUCCESS)
        while(1);

    if (IDEA_EncryptText(&idea_config) != IDEA_STATUS_SUCCESS)
        while(1);

    uint32_t cipher_len = IDEA_GetCipherTextLength(&idea_config);

    IDEA_GetIV(&idea_config, iv_used);

    printf("IV: ");
    for (size_t i = 0; i < 4; ++i)
    {
        printf("0x%04X ", iv_used[i]);
    }
    printf("\n");

    idea_config.textLen = cipher_len;
    if (IDEA_DecryptText(&idea_config) != IDEA_STATUS_SUCCESS)
        while(1);

    uint32_t decrypt_len = IDEA_GetCipherTextLength(&idea_config);

    printf("Plain text: %s\n", message);

    printf("Cipher text: ");
    for (size_t i = 0; i < sizeof(cipher) / sizeof(cipher[0]); ++i)
    {
        printf("0x%X ", cipher[i]);
    }
    printf("\n");

    printf("Decipher text: %s\nDecrypt length: %d\n", decipher, decrypt_len);

    while(1)
    {
        LED_ToggleOutput(5);
        delay(500);
    }

    return 0;
}
