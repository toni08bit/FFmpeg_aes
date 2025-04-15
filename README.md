# FFmpeg (AES) README

FFmpeg is a collection of libraries and tools to process multimedia content such as audio, video, subtitles, and related metadata. This repository is a modified version of FFmpeg with AES-CTR encryption and decryption to process encrypted video input and output, designed for secure and private video handling in shared or untrusted server environments.

## Project Description

This modified version of FFmpeg is designed to handle only encrypted input and output files. The input files must be AES-CTR encrypted with the keys generated during the build process using the `generate.sh` script. The output files will always be encrypted by the program using the same keys.

| Feature | **Standard FFmpeg** | **`toni08bit/FFmpeg_aes` (This Fork)** |
|---------|---------------------|----------------------------------------|
| **Encryption Support** | ⚠️ *Basic support via `-decryption_key` and external tools (e.g., AES-CBC)* | ✅ *Built-in AES-CTR (Counter mode) encryption/decryption at the I/O layer* |
| **Mode of Operation** | ⚠️ *AES-CBC / AES-ECB (when used externally)*<br>🟥 Susceptible to padding oracle attacks and block pattern leakage | ✅ *AES-CTR (stream cipher mode)*<br>🟩 No padding, supports random access, resistant to ciphertext pattern analysis |
| **Key Management** | ❌ *Manual and external; keys must be securely stored/transmitted by the developer* | ✅ *Keys and nonces securely generated at build-time using `generate.sh` and hardcoded into the binary* |
| **Encryption Transparency** | ❌ *Developer must pre/post-process using third-party tools* | ✅ *Encryption and decryption are fully transparent and integrated into FFmpeg's I/O pipeline* |
| **Input File Handling** | ❌ *Assumes plaintext input* | ✅ *Input must be AES-CTR encrypted with matched keys; secure-by-default pipeline* |
| **Output File Handling** | ❌ *Output is always plaintext unless externally encrypted post-process* | ✅ *Output is automatically AES-CTR encrypted using build-time keys* |
| **Security Posture in Untrusted Environments** | ⚠️ *Plaintext video files at rest; high risk in shared or cloud servers* | ✅ *No raw media ever written to disk; suitable for secure compute and CDN workflows* |
| **API / Codebase Changes** | ❌ *No encryption-focused API* | ✅ *Custom extensions in `ffmpeg_aes`, isolated and audit-friendly* |
| **Developer Overhead** | ⚠️ *Requires manual cryptographic routines and secure tooling integration* | ✅ *Zero-config encryption once compiled; simplifies OpSec in secure media pipelines* |

## Installation

To ensure the integrity and security of the encryption process, please follow these installation instructions carefully. Do not use `make install` or execute the `make` command directly.

1. Clone the repository:
   ```sh
   git clone https://github.com/toni08bit/FFmpeg_aes.git
   cd FFmpeg_aes
   ```

2. Configure FFmpeg with the necessary options:
   ```sh
   ./configure --enable-static --enable-gpl --enable-libx264 --enable-openssl --enable-version3
   ```

3. Run the `generate.sh` script to build the executables and generate the random keys:
   ```sh
   ./generate.sh
   ```

This script generates unique `aes_key` and `aes_nonce` for each input and output. These are the randomly generated, hardcoded keys for the encryption and decryption process.
You need to encrypt your input files with the aes_key_in and aes_nonce_in, the output will be encrypted by ffmpeg_aes using the aes_key_out and aes_nonce_out.

## Usage

### Encrypting and Decrypting Videos

All input and output files are automatically processed through an AES encryption or decryption layer. The FFmpeg commands will handle this implicitly, ensuring that all multimedia content is securely processed.

All other ffmpeg functionality remains the same.
Example command:
```sh
./ffmpeg_aes -i input.mp4 -c:v libx264 -c:a aac -b:a 192k -f mp4 output.mp4
```

The input file must be pre-encrypted, and the output file will be encrypted using the keys generated during the build process.

## Libraries

- `libavcodec` provides implementation of a wide range of codecs.
- `libavformat` implements streaming protocols, container formats, and basic I/O access.
- `libavutil` includes hashers, decompressors, and miscellaneous utility functions.
- `libavfilter` provides means to alter decoded audio and video through a directed graph of connected filters.
- `libavdevice` provides an abstraction to access capture and playback devices.
- `libswresample` implements audio mixing and resampling routines.
- `libswscale` implements color conversion and scaling routines.

## Tools

- [ffmpeg](https://ffmpeg.org/ffmpeg.html) is a command-line toolbox to manipulate, convert, and stream multimedia content.
- [ffplay](https://ffmpeg.org/ffplay.html) is a minimalistic multimedia player.
- [ffprobe](https://ffmpeg.org/ffprobe.html) is a simple analysis tool to inspect multimedia content.
- Additional small tools such as `aviocat`, `ismindex`, and `qt-faststart` are not modified further.
- (Only ffmpeg was tested extensively, but the other tools should work as expected.)

## Documentation

The offline documentation is available in the **doc/** directory.
The online documentation is available on the main [website](https://ffmpeg.org) and in the [wiki](https://trac.ffmpeg.org).

### Examples

Coding examples are available in the **doc/examples** directory.

## License

FFmpeg codebase is mainly LGPL-licensed with optional components licensed under GPL. Please refer to the LICENSE file for detailed information.

---

You can now copy this updated content and paste it into your [README.md file](https://github.com/toni08bit/FFmpeg_aes/edit/main/README.md).
