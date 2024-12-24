#!/bin/bash

format_hex() {
  echo "$1" | sed 's/../0x&, /g' | sed 's/, $//'
}

AES_KEY=$(openssl rand -hex 32)
AES_NONCE=$(openssl rand -hex 16)

FORMATTED_AES_KEY="{ $(format_hex "$AES_KEY") }"
FORMATTED_AES_NONCE="{ $(format_hex "$AES_NONCE") }"

touch ffmpeg_aes/secrets.c
make CFLAGS="-DAES_KEY='$FORMATTED_AES_KEY' -DAES_NONCE='$FORMATTED_AES_NONCE'"

if [ $? -ne 0 ]; then
    exit
fi

echo ""
echo ""
echo "----- !!! IMPORTANT KEYS !!! -----"
echo "AES_KEY: $AES_KEY"
echo "Formatted AES_KEY: $FORMATTED_AES_KEY"
echo "AES_NONCE: $AES_NONCE"
echo "Formatted AES_NONCE: $FORMATTED_AES_NONCE"
echo "---- !!! IMPORTANT KEYS !!! -----"
