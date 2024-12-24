/*
    IMPORTANT!
    Please DONT enter your keys here!
    The provided keys are examples for debugging purposes and SHOULD NOT BE USED IN ANY OTHER WAY. They do not server further purpose
    or unlock additional functionality.

    For further information please read INSTALL.md
*/


/* 256-bit AES Key */
// static const unsigned char aes_key_in[32] = AES_KEY_IN;
// static const unsigned char aes_key_out[32] = AES_KEY_OUT;

/* Initial Nonce (aka. IV) */
// static const unsigned char aes_nonce_in[16] = AES_NONCE_IN;
// static const unsigned char aes_nonce_out[16] = AES_NONCE_OUT;


/* DEBUGGING KEYS (should be commented out)*/
/* $openssl rand -hex 32 */
static const unsigned char aes_key_in[32] = { 0xee, 0x75, 0x11, 0x45, 0xd5, 0xbd, 0xfd, 0x74, 0x5c, 0x61, 0x84, 0xd4, 0x81, 0xa3, 0xba, 0x77, 0xf5, 0x15, 0x68, 0x10, 0x4c, 0x68, 0x6b, 0xde, 0x53, 0x28, 0x32, 0xab, 0xbd, 0x98, 0x65, 0xc4 };
/* $openssl rand -hex 16 */
static const unsigned char aes_nonce_in[16] = { 0xe2, 0x9e, 0x53, 0x10, 0xd3, 0xb1, 0xbe, 0x27, 0x09, 0xef, 0x4e, 0xed, 0x22, 0xd4, 0x02, 0x89 };
