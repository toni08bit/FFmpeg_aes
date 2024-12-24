#!/bin/bash

format_hex() {
  echo "$1" | sed 's/../0x&, /g' | sed 's/, $//'
}

AES_KEY_IN=$(openssl rand -hex 32)
AES_NONCE_IN=$(openssl rand -hex 16)
AES_KEY_OUT=$(openssl rand -hex 32)
AES_NONCE_OUT=$(openssl rand -hex 16)

FORMATTED_AES_KEY_IN="{ $(format_hex "$AES_KEY_IN") }"
FORMATTED_AES_NONCE_IN="{ $(format_hex "$AES_NONCE_IN") }"
FORMATTED_AES_KEY_OUT="{ $(format_hex "$AES_KEY_OUT") }"
FORMATTED_AES_NONCE_OUT="{ $(format_hex "$AES_NONCE_OUT") }"

touch ffmpeg_aes/secrets.c
make CFLAGS="-DAES_KEY_IN='$FORMATTED_AES_KEY_IN' -DAES_NONCE_IN='$FORMATTED_AES_NONCE_IN' -DAES_KEY_OUT='$FORMATTED_AES_KEY_OUT' -DAES_NONCE_OUT='$FORMATTED_AES_NONCE_OUT'"

if [ $? -ne 0 ]; then
    exit
fi

mv ffmpeg ffmpeg_aes

echo ""
echo ""
echo "----- !!! IMPORTANT KEYS !!! -----"
echo "AES_KEY_IN: $AES_KEY_IN"
# echo "Formatted AES_KEY_IN: $FORMATTED_AES_KEY_IN"
echo "AES_NONCE_IN: $AES_NONCE_IN"
# echo "Formatted AES_NONCE_IN: $FORMATTED_AES_NONCE_IN"
echo "----------------------------------"
echo "AES_KEY_OUT: $AES_KEY_OUT"
# echo "Formatted AES_KEY_OUT: $FORMATTED_AES_KEY_OUT"
echo "AES_NONCE_OUT: $AES_NONCE_OUT"
# echo "Formatted AES_NONCE_OUT: $FORMATTED_AES_NONCE_OUT"
echo "---- !!! IMPORTANT KEYS !!! -----"
