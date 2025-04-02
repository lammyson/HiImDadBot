# HiImDadBot

A Discord bot for some friends written in C++. It has the following features:
- It replies with `Hi <blank>! I'm dad!` whenever it detects a variation of the word `I'm `
- It contains a `/dadjoke` slash command that replies with a random dad joke or can reply with a selected dad joke

# Dependencies
- [DPP](https://github.com/brainboxdotcc/DPP)
  - Recommend installing a prebuilt release
    - If on Windows, the prebuilt release contains the Opus, OpenSSL, and zlib dependencies packaged with it
- [Opus](https://github.com/xiph/opus)
  - If on Linux, this will need to be installed to satisfy DPP's dependencies
- [OpenSSL](https://github.com/openssl/openssl)
  - Even though the [DPP](https://github.com/brainboxdotcc/DPP) Windows prebuilt release does contain OpenSSL, it still needs to be installed
- [zlib](https://github.com/madler/zlib)
  - If on Linux, this will need to be installed to satisfy DPP's dependencies

## Included Dependencies
- [RE2](https://github.com/google/re2)
- [Abseil](https://github.com/abseil/abseil-cpp)
- [GoogleTest](https://github.com/google/googletest) (only needed for testing)
