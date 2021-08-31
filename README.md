# dwh-hashkit

dwh-hashkit is a C library to check whether some data hashes to 3301's Deep Web Hash.

Make sure to enable MMX, AVX2, SSE4 or SSSE3 instructions at compile time for better performances. Since OpenSSL is used, make sure to link with its libraries (`ssl` and `crypto`).
For easier integration into any projects, no Makefile is required for instance ; you should only have to compile all `.c` files.

A set of test vectors is also included.

## Library

The core object of this library is the "hashbox", an object containing all hashing contexts. Its type is `hashbox_t`.

* `hashbox_t hashbox_new()` Creates a new hashbox and returns a pointer to the allocated memory. This memory should only be cleaning with a call to `hashbox_final(hashbox_t*)`. If `hashbox_new()` returns NULL, the hashbox should not be used.
* `void hashbox_update(hashbox_t*, uint8_t* data, uint32_t length)` sends `length` bytes in buffer `data` to be processed by the hashbox.
* `unsigned int hashbox_final(hashbox_t*)` returns an `unsigned int` `HASHBOX_*` constant, allowing you to know if the data processed matches the deep web hash. It also frees the hashbox. The hashbox object should not be used afterwards.

Constants :
* `HASHBOX_NO_MATCH`
* `HASHBOX_SHA512`
* `HASHBOX_BLAKE2B`
* `HASHBOX_STREEBOG`
* `HASHBOX_SHA3`
* `HASHBOX_FNV0`
* `HASHBOX_FNV1`
* `HASHBOX_FNV1A`
* `HASHBOX_GROSTL`
* `HASHBOX_MD6`
* `HASHBOX_JH`
* `HASHBOX_BLAKE512`
* `HASHBOX_LSH`
* `HASHBOX_SKEIN`
* `HASHBOX_KECCAK3`
* `HASHBOX_CUBEHASH`
* `HASHBOX_WHIRLPOOL0`
* `HASHBOX_WHIRLPOOLT`
* `HASHBOX_WHIRLPOOL`

## Example code :
```c
#include "hashbox.h"

int main() {
  hashbox_t* hashbox = hashbox_new();

  // Process "dwh-hashkit !"
  hashbox_update(hashbox, "dwh-hash", 8);
  hashbox_update(hashbox, "kit !", 5);

  if (hashbox_final(hashbox) != HASHBOX_NO_MATCH)
    puts("Congratulations !");
  else
    puts(":'(");

  // '*hashbox' is now freed and should not be used anymore.
}
```

## Hashes supported
 * SHA-512
 * BLAKE2b
 * Streebog
 * SHA-3
 * FNV-0/FNV-1/FNV-1a
 * Grøstl
 * MD6
 * JH
 * BLAKE-512
 * LSH
 * Skein
 * Keccak3
 * CubeHash
 * Whirlpool-0/Whirlpool-T/Whirlpool

## License
[GPLv3](https://www.gnu.org/licenses/gpl-3.0.html)
