#include <string.h>
#include <openssl/evp.h>

#include <libavutil/log.h>

#define BLOCK_SIZE 16

typedef struct {
    EVP_CIPHER_CTX *ecb_ctx;
    size_t stream_cursor;
} AesLayerContext;

static void increment_counter(const unsigned char *initial_counter, long increment, unsigned char *out_counter) {
    memcpy(out_counter,initial_counter,BLOCK_SIZE);

    for (int i = (BLOCK_SIZE - 1); (i >= 0) && (increment > 0); i--) {
        uint64_t sum = ((uint64_t)out_counter[i] + (increment & 0xFF));
        out_counter[i] = (unsigned char)(sum & 0xFF);
        increment >>= 8;
        if (sum > 0xFF) {
            increment += (sum >> 8);
        }
    }
}
static int aes_ctr_decrypt_blockwise(EVP_CIPHER_CTX *ecb_ctx, unsigned char *buf, size_t length, unsigned char *base_counter, size_t local_offset) {
    unsigned char keystream[BLOCK_SIZE];
    size_t processed = 0;
    size_t local_offset_edit = local_offset;
    size_t block_bytes;

    while (processed < length) {
        int output_len;
        int upd_ret;
        output_len = 0;
        upd_ret = EVP_EncryptUpdate(ecb_ctx, keystream, &output_len, base_counter, BLOCK_SIZE);
        if (upd_ret != 1) {
            av_log(NULL, AV_LOG_FATAL, "Failed to aes-decrypt a block.");
            return -1;
            // error
        }
        block_bytes = (BLOCK_SIZE - local_offset_edit);
        if (block_bytes > (length - processed)) {
            block_bytes = (length - processed);
        }

        for (size_t i = 0; i < block_bytes; i++) {
            buf[processed + i] ^= keystream[local_offset_edit + i];
        }

        processed += block_bytes;
        local_offset_edit = 0;

        if (processed < length) {
            for (int i = (BLOCK_SIZE - 1); i >= 0; i--) {
                base_counter[i]++;
                if (base_counter[i] != 0) {
                    break;
                }
            }
        }
    }
    return 0;
}
